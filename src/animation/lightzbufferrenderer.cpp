#include "lightzbufferrenderer.h"

#include "commontransformation.h"
#include "scaletransformation.h"
#include "src/number.h"

#include <omp.h>
#include <QPainter>

LightZBufferRenderer::LightZBufferRenderer(float scale, int32 width,
        int32 height) :
    Renderer(scale, width, height)
{
    zbuffer.setSize(width, height);
    buffer = new uchar[width * height * 4];
}

LightZBufferRenderer::~LightZBufferRenderer()
{
    delete buffer;
}


void LightZBufferRenderer::renderMesh(shared_ptr<Mesh> mesh)
{
    meshes.push_back(mesh);
}


void LightZBufferRenderer::addLight(SharedLight value)
{
    lights.push_back(value);
}

void LightZBufferRenderer::setCamera(SharedCamera value)
{
    camera = value;
}

uchar *LightZBufferRenderer::getRendered()
{
    return buffer;
}

void LightZBufferRenderer::putPixel(int32 x, int32 y, const Color &color)
{
    buffer[4 * (y * width + x) + 2] = color.getRed();
    buffer[4 * (y * width + x) + 1] = color.getGreen();
    buffer[4 * (y * width + x) + 0] = color.getBlue();
}


std::vector<float> LightZBufferRenderer::getBrezenhemX(const Vec3 &p1,
        const Vec3 &p2)
{
    float x1 = p1.x();
    float x2 = p2.x();
    int32 n = abs(static_cast<int>(p1.y() + 0.5) - static_cast<int>
                  (p2.y() + 0.5)) + 1;
    std::vector<float> result(n);
    float dx = (x2 - x1) / (n - 1);
    result[0] = x1;

    for (int32 i = 1; i < n; i++)
    {
        result[i] = result[i - 1] + dx;
    }

    return result;
}

std::vector<Vec3> LightZBufferRenderer::getNormals(const std::vector<float> &l,
        const Vec3 &n1, const Vec3 &n2)
{
    std::vector<Vec3> result;
    float s = l.size();

    for (uint32 i = 0; i < l.size(); i++)
    {
        if (s > 1)
        {
            result.push_back(n1 * ((s - i - 1) / (s - 1)) + n2 * (i / (s - 1)));
        }
        else
        {
            result.push_back((n1 + n2) * 0.5);
        }
    }

    return result;
}

std::vector<float> LightZBufferRenderer::getZLine(const Vec3 &p1,
        const Vec3 &p2, int32 n)
{
    float z1 = p1.z();
    float z2 = p2.z();
    std::vector<float> result(n);
    float dz = (z2 - z1) / (n - 1);
    result[0] = z1;

    for (int32 i = 1; i < n; i++)
    {
        result[i] = result[i - 1] + dz;
    }

    return result;
}


Color LightZBufferRenderer::calculateIntensity(const Vec3 &n, const Vec3 &orig,
        const Color &ka, const Color &kd, const Color &ks, float ns)
{
    Color result = 0;

    for (auto &light : lights)
    {
        result += light->getIntensity(n, orig, camera->getPosition(), ka, kd, ks, ns);
    }

    return result;
}

Vec3 toBarycenteric(const Vec3 &p, const Vec3 &a, const Vec3 &b, const Vec3 &c)
{
    Vec3 v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    return Vec3(u, v, w);
}
Vec3 toCartesian(const Vec3 &barycentric, const Vec3 &a, const Vec3 &b,
                 const Vec3 &c)
{
    return a * barycentric.x() + b * barycentric.y() + c * barycentric.z();
}

void LightZBufferRenderer::fillTriangle(Triangle &triangle)
{
    std::vector<float> lleft, lright;
    std::vector<float> zleft, zright;
    std::vector<Vec3> nleft, nright;
    bool swapped;
    getLeftRightBounds(lleft, lright, nleft, nright, zleft, zright, triangle,
                       swapped);
    const Vec3 &wv1 = projected[triangle.getV1()],
                &wv2 = projected[triangle.getV2()],
                 &wv3 = projected[triangle.getV3()];
    auto ka = currentMesh->getMaterial().getKa();
    auto kd = currentMesh->getMaterial().getKd();
    auto ks = currentMesh->getMaterial().getKs();
    auto ns = currentMesh->getMaterial().getNs();
    Vec3 ov1 = currentMesh->getVertices()[triangle.getV1()].getV();
    Vec3 ov2 = currentMesh->getVertices()[triangle.getV2()].getV();
    Vec3 ov3 = currentMesh->getVertices()[triangle.getV3()].getV();
    int32 miny = round(wv1.y());
    int32 maxy = round(wv3.y());

    if (miny == maxy)
    {
        return;
    }

    for (int32 y = miny, i = 0; y <= maxy; y++, i++)
    {
        Vec3 n1 = nleft[i], n2 = nright[i];
        float x1 = lleft[i], x2 = lright[i];
        int32 s = abs(static_cast<int>(x2 + 0.5) - static_cast<int>(x1 + 0.5));
        float dx = (x2 - x1) / s;
        float z1 = zleft[i], z2 = zright[i];
        float dz = (z2 - z1) / s;
        float z = z1;
        float x = x1;

        for (int32 j = 0; j < s + 1; j++)
        {
            int32 ix = x + 0.5, iy = y + 0.5;

            if (!(ix < 0 || ix >= width || iy < 0 || iy >= height) &&
                    z < zbuffer.get(ix, iy))
            {
                zbuffer.set(ix, iy, z);
                Vec3 n;
                float part = (float)j / s;

                if (s > 1)
                {
                    n = n1 * (1 - part) + n2 * part;
                }
                else
                {
                    n = n1;
                }

                Vec3 orig = toCartesian(toBarycenteric(Vec3(x, y, z), wv1, wv2,
                                                       wv3), ov1, ov2, ov3);
                Color intensity = calculateIntensity(n, orig, ka, kd, ks, ns);
                putPixel(ix, iy, intensity);
            }

            z += dz;
            x += dx;
        }
    }
}

void LightZBufferRenderer::getLeftRightBounds(std::vector<float> &lleft,
        std::vector<float> &lright,
        std::vector<Vec3> &nleft, std::vector<Vec3> &nright, std::vector<float> &zleft,
        std::vector<float> &zright,
        Triangle &triangle, bool &swapped)
{
    triangleSort(projected, triangle);
    const Vec3 &wv1 = projected[triangle.getV1()],
                &wv2 = projected[triangle.getV2()],
                 &wv3 = projected[triangle.getV3()];
    std::vector<float> l1 = getBrezenhemX(wv1, wv2);
    std::vector<float> l2 = getBrezenhemX(wv2, wv3);
    std::vector<float> l3 = getBrezenhemX(wv1, wv3);
    std::vector<Vec3> n1 = getNormals(l1,
                                      currentMesh->getVertices()[triangle.getV1()].getN(),
                                      currentMesh->getVertices()[triangle.getV2()].getN());
    std::vector<Vec3> n2 = getNormals(l2,
                                      currentMesh->getVertices()[triangle.getV2()].getN(),
                                      currentMesh->getVertices()[triangle.getV3()].getN());
    std::vector<Vec3> n3 = getNormals(l3,
                                      currentMesh->getVertices()[triangle.getV1()].getN(),
                                      currentMesh->getVertices()[triangle.getV3()].getN());
    std::vector<float> z1 = getZLine(wv1, wv2, l1.size());
    std::vector<float> z2 = getZLine(wv2, wv3, l2.size());
    std::vector<float> z3 = getZLine(wv1, wv3, l3.size());
    l1.pop_back();
    l1.insert(l1.end(), l2.begin(), l2.end());
    n1.pop_back();
    n1.insert(n1.end(), n2.begin(), n2.end());
    z1.pop_back();
    z1.insert(z1.end(), z2.begin(), z2.end());
    int32 length = l3.size();
    int32 m = length / 2;

    if (l1[m] < l3[m])
    {
        lleft = std::move(l1);
        lright = std::move(l3);
        nleft = std::move(n1);
        nright = std::move(n3);
        zleft = std::move(z1);
        zright = std::move(z3);
        swapped = false;
    }
    else
    {
        lleft = std::move(l3);
        lright = std::move(l1);
        nleft = std::move(n3);
        nright = std::move(n1);
        zleft = std::move(z3);
        zright = std::move(z1);
        swapped = true;
    }
}

void LightZBufferRenderer::triangleSort(const std::vector<Vec3> &vertices,
                                        Triangle &triangle)
{
    auto swap = [](int32 & a, int32 & b)
    {
        int32 t = a;
        a = b;
        b = t;
    };
    int32 i1 = triangle.getV1(), i2 = triangle.getV2(), i3 = triangle.getV3();

    if (vertices.at(i2).y() < vertices.at(i1).y())
    {
        swap(i2, i1);
    }

    if (vertices.at(i3).y() < vertices.at(i1).y())
    {
        swap(i3, i1);
    }

    if (vertices.at(i3).y() < vertices.at(i2).y())
    {
        swap(i3, i2);
    }

    triangle.setV1(i1);
    triangle.setV2(i2);
    triangle.setV3(i3);
}


void LightZBufferRenderer::start(int32 width, int32 height)
{
    this->width = width;
    this->height = height;
    zbuffer.setSize(width, height);
    zbuffer.init();
    this->scale = scale;
    delete buffer;
    buffer = new uchar[width * height * 4];

    for (int32 i = 0; i < width * height; i++)
    {
        buffer[4 * i] = 231;
        buffer[4 * i + 1] = 235;
        buffer[4 * i + 2] = 239;
    }
}

void LightZBufferRenderer::finish()
{
    CommonTransformation perspective(camera->getPVMatrix());
    float scalex = width / 2;
    float scaley = height / 2;
    scale = scalex > scaley ? scaley : scalex;

    for (auto &mesh : meshes)
    {
        currentMesh = mesh;
        projected.clear();
        projected.reserve(currentMesh->getVertices().size());

        for (auto &vertex : currentMesh->getVertices())
        {
            Vec3 v = vertex.getV();
            perspective.transform(v);
            v.setX(v.x() * scale + width / 2);
            v.setY(v.y() * scale + height / 2);
            projected.push_back(v);
        }

        auto &triangles = currentMesh->getTriangles();

        for (auto &triangle : triangles)
        {
            fillTriangle(triangle);
        }
    }

    lights.clear();
    meshes.clear();
}

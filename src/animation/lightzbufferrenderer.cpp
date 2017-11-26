#include "lightzbufferrenderer.h"

#include "commontransformation.h"
#include "scaletransformation.h"

#include <omp.h>
#include <QPainter>

LightZBufferRenderer::LightZBufferRenderer(float scale, int width,
        int height) :
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

void LightZBufferRenderer::putPixel(int x, int y, const Color &color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        buffer[4 * (y * width + x)] = color.getRed();
        buffer[4 * (y * width + x) + 1] = color.getGreen();
        buffer[4 * (y * width + x) + 2] = color.getBlue();
    }
}


std::vector<int> LightZBufferRenderer::getBrezenhemX(const Vec3 &p1,
        const Vec3 &p2)
{
    std::vector<int> result;
    int32 x1 = round(p1.x()), y1 = round(p1.y());
    int32 x2 = round(p2.x()), y2 = round(p2.y());

    if (x1 == x2 && y1 == y2)
    {
        result.push_back(x1);
        return result;
    }

    int32 dx = x2 - x1, dy = y2 - y1;
    int32 sx = Math::sgn(dx);
    dx = abs(dx);
    dy = abs(dy);
    bool flag = dy > dx;

    if (flag)
    {
        std::swap(dx, dy);
    }

    int32 f = (dy << 1) - dx;
    int32 x = x1;

    if (flag)
    {
        for (int32 i = 0; i <= dx; i++)
        {
            result.push_back(x);

            if (f > 0)
            {
                x += sx;
                f -= dx * 2;
            }

            f += dy * 2;
        }
    }
    else
    {
        if (f <= 0)
        {
            result.push_back(x);
        }

        for (int32 i = 0; i <= dx; i++)
        {
            if (f > 0)
            {
                result.push_back(x);
                f -= dx * 2;
            }

            x += sx;
            f += dy * 2;
        }
    }

    return result;
}

std::vector<Vec3> LightZBufferRenderer::getNormals(const std::vector<int> &l,
        const Vec3 &n1, const Vec3 &n2)
{
    std::vector<Vec3> result;
    float s = l.size();

    for (uint i = 0; i < l.size(); i++)
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
        const Vec3 &p2, int n)
{
    float z1 = p1.z();
    float z2 = p2.z();
    std::vector<float> result(n);
    float dz = (z2 - z1) / (n - 1);
    result[0] = z1;

    for (int i = 1; i < n; i++)
    {
        result[i] = result[i - 1] + dz;
    }

    return result;
}


float LightZBufferRenderer::calculateIntensity(const Vec3 &n, const Vec3 &orig)
{
    float result = 0;

    for (auto &light : lights)
    {
        result += light->getIntensity(n, orig, camera->getPosition());
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
    std::vector<int> lleft, lright;
    std::vector<float> zleft, zright;
    std::vector<Vec3> nleft, nright;
    bool swapped;
    getLeftRightBounds(lleft, lright, nleft, nright, zleft, zright, triangle,
                       swapped);
    const Vec3 &wv1 = projected[triangle.getV1()],
                &wv2 = projected[triangle.getV2()],
                 &wv3 = projected[triangle.getV3()];
    auto color = currentMesh->getMaterial().getKd();
    Vec3 ov1 = currentMesh->getVertices()[triangle.getV1()].getV();
    Vec3 ov2 = currentMesh->getVertices()[triangle.getV2()].getV();
    Vec3 ov3 = currentMesh->getVertices()[triangle.getV3()].getV();
    int miny = round(wv1.y());
    int maxy = round(wv3.y());

    if (miny == maxy)
    {
        return;
    }

    for (int y = miny, i = 0; y <= maxy; y++, i++)
    {
        Vec3 n1 = nleft[i], n2 = nright[i];
        float s = lright[i] - lleft[i] + 1;
        float z1 = zleft[i], z2 = zright[i];
        float dz = (z2 - z1) / (lright[i] - lleft[i]);
        float z = z1;

        for (int x = lleft[i], j = 0; x <= lright[i]; x++, j++)
        {
            if (x < 0 || x >= width || y < 0 || y >= height)
            {
                continue;
            }

            float old = zbuffer.get(x, y);

            if (z < zbuffer.get(x, y))
            {
                zbuffer.set(x, y, z);
                Vec3 n;
                float part = (j / (s - 1));

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
                float intensity = calculateIntensity(n, orig);
                putPixel(x, y, color * intensity);
            }

            z += dz;
        }
    }
}

void LightZBufferRenderer::getLeftRightBounds(std::vector<int> &lleft,
        std::vector<int> &lright,
        std::vector<Vec3> &nleft, std::vector<Vec3> &nright, std::vector<float> &zleft,
        std::vector<float> &zright,
        Triangle &triangle, bool &swapped)
{
    triangleSort(projected, triangle);
    const Vec3 &wv1 = projected[triangle.getV1()],
                &wv2 = projected[triangle.getV2()],
                 &wv3 = projected[triangle.getV3()];
    std::vector<int> l1 = getBrezenhemX(wv1, wv2);
    std::vector<int> l2 = getBrezenhemX(wv2, wv3);
    std::vector<int> l3 = getBrezenhemX(wv1, wv3);
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
    int length = l3.size();
    int m = length / 2;

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
    auto swap = [](int &a, int &b)
    {
        int t = a;
        a = b;
        b = t;
    };
    int i1 = triangle.getV1(), i2 = triangle.getV2(), i3 = triangle.getV3();

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


void LightZBufferRenderer::start(float scale, int width, int height)
{
    this->width = width;
    this->height = height;
    zbuffer.setSize(width, height);
    zbuffer.init();
    this->scale = scale;
    delete buffer;
    buffer = new uchar[width * height * 4];

    for (int i = 0; i < width * height; i++)
    {
        buffer[4 * i] = 33;
        buffer[4 * i + 1] = 33;
        buffer[4 * i + 2] = 33;
    }
}

void LightZBufferRenderer::finish()
{
    CommonTransformation perspective(camera->getPVMatrix());
    CommonTransformation pm(camera->getPMatrix());
    CommonTransformation vm(camera->getVMatrix());
    auto eye = Vec3(0, 0, -1);
    float scalex = width / 2;
    float scaley = height / 2;
    scale = scalex > scaley ? scaley : scalex;

    for (auto &mesh : meshes)
    {
        currentMesh = mesh;
        projected.clear();
        projected.reserve(currentMesh->getVertices().size());
        //projected = currentMesh->getVertices();

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
            //            auto v1 = projected[triangle.getV1()].getV();
            //            auto v2 = projected[triangle.getV2()].getV();
            //            auto v3 = projected[triangle.getV3()].getV();
            //            Vec3 u = v2 - v1;
            //            Vec3 v = v3 - v1;
            //            Vec3 n = u.cross(v);
            //            if (n.dot(projected[triangle.getV3()].getN()) < 0)
            //            {
            //                n = -n;
            //            }
            //            if (n.dot(eye) > 0)
            //            {
            fillTriangle(triangle);
            //            }
        }
    }

    lights.clear();
    meshes.clear();
}

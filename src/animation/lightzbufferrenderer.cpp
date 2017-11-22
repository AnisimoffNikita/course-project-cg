#include "lightzbufferrenderer.h"

#include "commontransformation.h"

#include <QPainter>

LightZBufferRenderer::LightZBufferRenderer(double scale, int32 width,
        int32 height) :
    Renderer(scale, width, height)
{
    canvas.fill(Qt::white);
    buffer.setSize(width, height);
}

LightZBufferRenderer::~LightZBufferRenderer()
{
}


void LightZBufferRenderer::renderMesh(const Mesh &mesh)
{
    currentMesh = mesh;
    projected = mesh.getVertices();
    CommonTransformation perspective(camera->getPVMatrix());
    Vec3 center(width / 2, height / 2, 0);

    for (auto &v : projected)
    {
        perspective.transform(v);
        v = v * scale + center;
    }

    auto triangles = mesh.getTriangles();

    for (const auto &triangle : triangles)
    {
        //        auto eye = camera->getEyeVector();
        //        auto v1 = currentMesh.getVertices()[triangle.v1()];
        //        auto v2 = currentMesh.getVertices()[triangle.v2()];
        //        auto v3 = currentMesh.getVertices()[triangle.v3()];
        //        Vertex u = v2 - v1;
        //        Vertex v = v3 - v1;
        //        Vertex n = u.cross(v);
        //        if (n.dot(currentMesh.getNormals()[triangle.n1()]) < 0)
        //        {
        //            n = -n;
        //        }
        //        if (n.dot(eye) > 0)
        //        {
        fillTriangle(triangle);
        //        }
    }
}


void LightZBufferRenderer::addLight(SharedLight value)
{
    lights.push_back(value);
}

void LightZBufferRenderer::setCamera(SharedCamera value)
{
    camera = value;
}

QImage LightZBufferRenderer::getRendered()
{
    auto toReturn = canvas;
    canvas.fill(Qt::lightGray);
    lights.clear();
    buffer.init();
    return toReturn;
}

std::vector<int> LightZBufferRenderer::getBrezenhemY(const Vec3 &p1,
        const Vec3 &p2)
{
    std::vector<int> result;
    int32 x1 = p1.x(), y1 = p1.y();
    int32 x2 = p2.x(), y2 = p2.y();

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
        for (int32 i = 0; i < dx; i++)
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
        for (int32 i = 0; i < dx; i++)
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

    result.push_back(x);
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

double LightZBufferRenderer::calculateIntensity(const Vec3 &n)
{
    double result = 0;

    for (auto &light : lights)
    {
        result += light->getIntensity(n);
    }

    return result;
}


void LightZBufferRenderer::fillTriangle(const Triangle &triangle)
{
    Triangle sortedTriangle = triangle;
    triangleSort(projected, sortedTriangle);
    Vec3 wv1 = projected[sortedTriangle.v1()],
           wv2 = projected[sortedTriangle.v2()],
           wv3 = projected[sortedTriangle.v3()];
    std::vector<int> l1 = getBrezenhemY(wv1, wv2);
    std::vector<int> l2 = getBrezenhemY(wv2, wv3);
    std::vector<int> l3 = getBrezenhemY(wv1, wv3);
    auto normals = currentMesh.getNormals();
    std::vector<Vec3> n1 = getNormals(l1, normals[sortedTriangle.n1()],
                                        normals[sortedTriangle.n2()]);
    std::vector<Vec3> n2 = getNormals(l2, normals[sortedTriangle.n2()],
                                        normals[sortedTriangle.n3()]);
    std::vector<Vec3> n3 = getNormals(l3, normals[sortedTriangle.n1()],
                                        normals[sortedTriangle.n3()]);
    l1.pop_back();
    l1.insert(l1.end(), l2.begin(), l2.end());
    n1.pop_back();
    n1.insert(n1.end(), n2.begin(), n2.end());
    std::vector<int> lleft, lright;
    std::vector<Vec3> nleft, nright;
    int length = l3.size();
    int m = length / 2;

    if (l1[m] < l3[m])
    {
        lleft = std::move(l1);
        lright = std::move(l3);
        nleft = std::move(n1);
        nright = std::move(n3);
    }
    else
    {
        lleft = std::move(l3);
        lright = std::move(l1);
        nleft = std::move(n3);
        nright = std::move(n1);
    }

    Vec3 u = wv2 - wv1;
    Vec3 v = wv3 - wv1;
    Vec3 n = u.cross(v);
    double a = n.x(), b = n.y(), c = n.z();
    double d = - (a * wv1.x() + b * wv1.y() + c * wv1.z());

    if (c == 0)
    {
        return;
    }

    auto color = currentMesh.getMaterial().getDiffuseColor();
    double z;

    for (int y = wv1.y(), i = 0; y <= wv3.y(); y++, i++)
    {
        Vec3 n1 = nleft[i], n2 = nright[i];
        float s = lright[i] - lleft[i] + 1;

        for (int x = lleft[i], j = 0; x <= lright[i]; x++, j++)
        {
            z = -(a * x + b * y + d) / c;

            if (z > buffer.get(x, y))
            {
                if (!(x >= 0 && x < width && y >= 0 && y < height))
                {
                    continue;
                }

                buffer.set(x, y, z);
                Vec3 n;

                if (s > 1)
                {
                    n = n1 * ((s - j - 1) / (s - 1)) + n2 * (j / (s - 1));
                }
                else
                {
                    n = (n1 + n2) * 0.5;
                }

                double intensity = calculateIntensity(n);
                int r = color.getRed() * intensity;

                if (r > 255)
                {
                    r = 255;
                }

                int g = color.getGreen() * intensity;

                if (g > 255)
                {
                    g = 255;
                }

                int b = color.getBlue() * intensity;

                if (b > 255)
                {
                    b = 255;
                }

                QColor qcolor(r, b, g);
                canvas.setPixelColor(x, y, qcolor);
            }
        }
    }
}

void LightZBufferRenderer::triangleSort(const std::vector<Vec3> &vertices,
                                        Triangle &triangle)
{
    if (vertices.at(triangle.v2()).y() < vertices.at(triangle.v1()).y())
    {
        int temp = triangle.v1();
        triangle.setV1(triangle.v2());
        triangle.setV2(temp);
        temp = triangle.n1();
        triangle.setN1(triangle.n2());
        triangle.setN2(temp);
    }

    if (vertices.at(triangle.v3()).y() < vertices.at(triangle.v1()).y())
    {
        int temp = triangle.v1();
        triangle.setV1(triangle.v3());
        triangle.setV3(temp);
        temp = triangle.n1();
        triangle.setN1(triangle.n3());
        triangle.setN3(temp);
    }

    if (vertices.at(triangle.v3()).y() < vertices.at(triangle.v2()).y())
    {
        int temp = triangle.v3();
        triangle.setV3(triangle.v2());
        triangle.setV2(temp);
        temp = triangle.n3();
        triangle.setN3(triangle.n2());
        triangle.setN2(temp);
    }
}

#include "lightzbufferrenderer.h"

#include "commontransformation.h"
#include "scaletransformation.h"

#include <QPainter>

LightZBufferRenderer::LightZBufferRenderer(double scale, int32 width,
        int32 height) :
    Renderer(scale, width, height)
{
    canvas.fill(Qt::lightGray);
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
        v.transform(perspective);
        v.setV(v.getV()*scale + center);
    }

    auto triangles = mesh.getTriangles();

    for (const auto &triangle : triangles)
    {
        auto eye = Vec3(0, 0, -1);
        auto v1 = projected[triangle.getV1()].getV();
        auto v2 = projected[triangle.getV2()].getV();
        auto v3 = projected[triangle.getV3()].getV();
        Vec3 u = v2 - v1;
        Vec3 v = v3 - v1;
        Vec3 n = u.cross(v);

        if (n.dot(projected[triangle.getV1()].getN()) > 0)
        {
            n = -n;
        }

        if (n.dot(eye) > 0)
        {
            fillTriangle(triangle);
        }
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

void LightZBufferRenderer::putPixel(int x, int y, const Color &color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        QColor qcolor(color.getRed(), color.getGreen(), color.getBlue());
        canvas.setPixelColor(x, y , qcolor);
    }
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
    Vertex wv1 = projected[sortedTriangle.getV1()],
           wv2 = projected[sortedTriangle.getV2()],
           wv3 = projected[sortedTriangle.getV3()];
    std::vector<int> l1 = getBrezenhemY(wv1.getV(), wv2.getV());
    std::vector<int> l2 = getBrezenhemY(wv2.getV(), wv3.getV());
    std::vector<int> l3 = getBrezenhemY(wv1.getV(), wv3.getV());
    std::vector<Vec3> n1 = getNormals(l1,
                                      currentMesh.getVertices()[sortedTriangle.getV1()].getN(),
                                      currentMesh.getVertices()[sortedTriangle.getV2()].getN());
    std::vector<Vec3> n2 = getNormals(l2,
                                      currentMesh.getVertices()[sortedTriangle.getV2()].getN(),
                                      currentMesh.getVertices()[sortedTriangle.getV3()].getN());
    std::vector<Vec3> n3 = getNormals(l3,
                                      currentMesh.getVertices()[sortedTriangle.getV1()].getN(),
                                      currentMesh.getVertices()[sortedTriangle.getV3()].getN());
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

    Vec3 u = wv2.getV() - wv1.getV();
    Vec3 v = wv3.getV() - wv1.getV();
    Vec3 n = u.cross(v);
    double a = n.x(), b = n.y(), c = n.z();
    double d = - (a * wv1.getV().x() + b * wv1.getV().y() + c * wv1.getV().z());

    if (c == 0)
    {
        return;
    }

    auto color = currentMesh.getMaterial().getKd();
    double z;

    for (int y = wv1.getV().y(), i = 0; y <= wv3.getV().y(); y++, i++)
    {
        Vec3 n1 = nleft[i], n2 = nright[i];
        float s = lright[i] - lleft[i] + 1;

        for (int x = lleft[i], j = 0; x <= lright[i]; x++, j++)
        {
            z = -(a * x + b * y + d) / c;

            if (z > buffer.get(x, y))
            {
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

                if (r > 240)
                {
                    r = 255;
                }

                int g = color.getGreen() * intensity;

                if (g > 240)
                {
                    g = 255;
                }

                int b = color.getBlue() * intensity;

                if (b > 240)
                {
                    b = 255;
                }

                putPixel(x, y, Color(r, g, b));
            }
        }
    }
}

void LightZBufferRenderer::triangleSort(const std::vector<Vertex> &vertices,
                                        Triangle &triangle)
{
    auto swap = [](int &a, int &b)
    {
        int t = a;
        a = b;
        b = t;
    };
    int i1 = triangle.getV1(), i2 = triangle.getV2(), i3 = triangle.getV3();

    if (vertices.at(i2).getV().y() < vertices.at(i1).getV().y())
    {
        swap(i2, i1);
    }

    if (vertices.at(i3).getV().y() < vertices.at(i1).getV().y())
    {
        swap(i3, i1);
    }

    if (vertices.at(i3).getV().y() < vertices.at(i2).getV().y())
    {
        swap(i3, i2);
    }

    triangle.setV1(i1);
    triangle.setV2(i2);
    triangle.setV3(i3);
}

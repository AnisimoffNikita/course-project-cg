#include "zbufferrenderer.h"

#include "commontransformation.h"

#include <QPainter>

ZBufferRenderer::ZBufferRenderer(double scale, int32 width, int32 height) :
    Renderer(scale, width, height)
{
    canvas.fill(Qt::white);
    buffer.setSize(width, height);
}

ZBufferRenderer::~ZBufferRenderer()
{
}


void ZBufferRenderer::renderMesh(const Mesh &mesh)
{
    currentMesh = mesh;
    auto vertices = mesh.getVertices();
    auto triangles = mesh.getTriangles();
    CommonTransformation perspective(camera->getPVMatrix());

    for (auto &vertex : vertices)
    {
        vertex.transform(perspective);
    }

    for (const auto &triangle : triangles)
    {
        Vertex v1 = vertices.at(triangle.getV1());
        Vertex v2 = vertices.at(triangle.getV2());
        Vertex v3 = vertices.at(triangle.getV3());
        fillTriangle(v1, v2, v3);
    }
}


void ZBufferRenderer::addLight(SharedLight)
{
}

void ZBufferRenderer::setCamera(SharedCamera value)
{
    camera = value;
}

QImage ZBufferRenderer::getRendered()
{
    auto toReturn = canvas;
    canvas.fill(Qt::white);
    buffer.init();
    return toReturn;
}

void ZBufferRenderer::putPixel(int x, int y, const Color &color)
{
    QColor qcolor(color.getRed(), color.getGreen(), color.getBlue());
    canvas.setPixelColor(x * scale + width / 2, y * scale + width, qcolor);
}

std::vector<int> ZBufferRenderer::getBrezenhemX(const Vec3 &p1,
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


void ZBufferRenderer::fillTriangle(const Vertex &v1, const Vertex &v2,
                                   const Vertex &v3)
{
    //    Vec3 wv1 = v1, wv2 = v2, wv3 = v3;
    //    verticesSort(wv1, wv2, wv3);
    //    std::vector<int> l1 = getBrezenhemX(wv1, wv2);
    //    std::vector<int> l2 = getBrezenhemX(wv2, wv3);
    //    std::vector<int> l3 = getBrezenhemX(wv1, wv3);
    //    l1.pop_back();
    //    l1.insert(l1.end(), l2.begin(), l2.end());
    //    std::vector<int> left, right;
    //    int length = l3.size();
    //    int m = length / 2;
    //    if (l1[m] < l3[m])
    //    {
    //        left = std::move(l1);
    //        right = std::move(l3);
    //    }
    //    else
    //    {
    //        left = std::move(l3);
    //        right = std::move(l1);
    //    }
    //    Vec3 u = wv2 - wv1;
    //    Vec3 v = wv3 - wv1;
    //    Vec3 n = u.cross(v);
    //    double a = n.x(), b = n.y(), c = n.z();
    //    double d = - (a * wv1.x() + b * wv1.y() + c * wv1.z());
    //    if (c == 0)
    //    {
    //        return;
    //    }
    //    auto color = currentMesh.getMaterial().getKd();
    //    double z;
    //    for (int y = wv1.y(), i = 0; y <= wv3.y(); y++, i++)
    //    {
    //        for (int x = left[i]; x <= right[i]; x++)
    //        {
    //            z = -(a * x + b * y + d) / c;
    //            if (z > buffer.get(x, y))
    //            {
    //                buffer.set(x, y, z);
    //                canvas.setPixelColor(x, y, qcolor);
    //            }
    //        }
    //        z = -(a * left[i] + b * y + d) / c;
    //        if (z >= buffer.get(left[i], y))
    //        {
    //            buffer.set(left[i], y, z);
    //            canvas.setPixelColor(left[i], y, Qt::black);
    //        }
    //        z = -(a * right[i] + b * y + d) / c;
    //        if (z >= buffer.get(right[i], y))
    //        {
    //            buffer.set(right[i], y, z);
    //            canvas.setPixelColor(right[i], y, Qt::black);
    //        }
    //    }
}

void ZBufferRenderer::verticesSort(Vec3 &v1, Vec3 &v2, Vec3 &v3)
{
    auto swap = [](Vec3 & a, Vec3 & b)
    {
        Vec3 t = a;
        a = b;
        b = t;
    };

    if (v2.y() < v1.y())
    {
        swap(v2, v1);
    }

    if (v3.y() < v1.y())
    {
        swap(v3, v1);
    }

    if (v3.y() < v2.y())
    {
        swap(v3, v2);
    }
}

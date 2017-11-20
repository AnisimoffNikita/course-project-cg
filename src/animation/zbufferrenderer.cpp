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
    if (camera.expired())
        return;

    auto workCamera = camera.lock();

    auto vertices = mesh.getVertices();

    CommonTransformation perspective(workCamera->getPVMatrix());

    Vertex center(width/2, height/2, 0);

    for (auto &v : vertices)
    {
        perspective.transform(v);
        v = v*scale + center;
    }

    auto triangles = mesh.getTriangles();

    auto color = mesh.getMaterial().getDiffuseColor();

    for (const auto& triangle : triangles)
    {
        Vertex v1 = vertices.at(triangle.v1());
        Vertex v2 = vertices.at(triangle.v2());
        Vertex v3 = vertices.at(triangle.v3());

        fillTriangle(v1, v2, v3, color);
    }

}


void ZBufferRenderer::addLight(WeakLight)
{
}

void ZBufferRenderer::setCamera(WeakCamera value)
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



std::vector<int> ZBufferRenderer::getBrezenhemX(const Vertex &p1, const Vertex &p2)
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
    dx = abs(dx); dy = abs(dy);
    bool flag = dy > dx;
    if (flag)
    {
        std::swap(dx, dy);
    }
    int32 f = (dy<<1) - dx;
    int32 x = x1;

    if (flag)
    {
        for (int32 i = 0; i < dx; i++)
        {
            result.push_back(x);
            if (f > 0)
            {
                x += sx;
                f -= dx*2;
            }
            f += dy*2;
        }
    }
    else
    {
        for (int32 i = 0; i < dx; i++)
        {
            if (f > 0)
            {
                result.push_back(x);
                f -= dx*2;
            }
            x += sx;
            f += dy*2;
        }
    }
    result.push_back(x);

    return result;
}


void ZBufferRenderer::fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Color &color)
{
    auto swap = [](Vertex &a, Vertex &b)
    {
        Vertex t = a;
        a = b;
        b = t;
    };

    Vertex wv1 = v1, wv2 = v2, wv3 = v3;

    if (wv2.y() < wv1.y())
    {
        swap(wv2, wv1);
    }
    if (wv3.y() < wv1.y())
    {
        swap(wv3, wv1);
    }
    if (wv3.y() < wv2.y())
    {
        swap(wv3, wv2);
    }

    std::vector<int> l12 = getBrezenhemX(wv1, wv2);
    std::vector<int> l23 = getBrezenhemX(wv2, wv3);
    std::vector<int> l13 = getBrezenhemX(wv1, wv3);

    l12.pop_back();
    l12.insert(l12.end(), l23.begin(), l23.end());

    std::vector<int> left, right;

    int length = l13.size();
    int m = length / 2;

    if (l12[m] < l13[m])
    {
        left = std::move(l12);
        right = std::move(l13);
    }
    else
    {
        left = l13;
        right = l12;
    }

    Vertex u = wv2-wv1;
    Vertex v = wv3-wv1;
    Vertex n = u.cross(v);
    double a = n.x(), b = n.y(), c = n.z();
    double d = - (a*wv1.x() + b*wv1.y() + c*wv1.z());

    if (c == 0)
        return;

    QColor qcolor(color.getRed(), color.getGreen(), color.getBlue());

    double z;
    for (int y = wv1.y(), i = 0; y <= wv3.y(); y++, i++)
    {

        for (int x = left[i]; x <= right[i]; x++)
        {
            z = -(a*x+b*y+d)/c;
            if (z > buffer.get(x, y))
            {
                buffer.set(x, y, z);
                canvas.setPixelColor(x, y, qcolor);
            }
        }
        z = -(a*left[i]+b*y+d)/c;
        if (z >= buffer.get(left[i], y))
        {
            buffer.set(left[i], y, z);
            canvas.setPixelColor(left[i], y, Qt::black);
        }
        z = -(a*right[i]+b*y+d)/c;
        if (z >= buffer.get(right[i], y))
        {
            buffer.set(right[i], y, z);
            canvas.setPixelColor(right[i], y, Qt::black);
        }

    }
}


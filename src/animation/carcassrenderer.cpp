#include "carcassrenderer.h"

#include "commontransformation.h"

#include <QPainter>

CarcassRenderer::CarcassRenderer(double scale, int32 width, int32 height) :
    Renderer(scale, width, height)
{
    canvas.fill(Qt::white);
}


void CarcassRenderer::renderMesh(const Mesh &mesh)
{
    auto vertices = mesh.getVertices();
    CommonTransformation perspective(camera->getPVMatrix());
    Vec3 center(width / 2, height / 2, 0);

    for (auto &v : vertices)
    {
        perspective.transform(v);
        v = v * scale + center;
    }

    auto edges = mesh.getEdges();

    for (const auto &edge : edges)
    {
        Vec3 v1 = vertices.at(edge.v1());
        Vec3 v2 = vertices.at(edge.v2());
        brezenhem(v1, v2);
    }
}

void CarcassRenderer::brezenhem(const Vec3 &p1, const Vec3 &p2)
{
    int32 x1 = p1.x(), y1 = p1.y();
    int32 x2 = p2.x(), y2 = p2.y();

    if (x1 == x2 && y1 == y2)
    {
        canvas.setPixelColor(y1, x1, Qt::black);
    }

    int32 dx = x2 - x1, dy = y2 - y1;
    int32 sx = Math::sgn(dx), sy = Math::sgn(dy);
    dx = abs(dx);
    dy = abs(dy);
    bool flag = dy > dx;

    if (flag)
    {
        std::swap(dx, dy);
    }

    int32 f = (dy << 1) - dx;
    int32 x = x1, y = y1;

    if (flag)
    {
        for (int32 i = 0; i < dx; i++)
        {
            canvas.setPixelColor(x, y, Qt::black);

            if (f > 0)
            {
                x += sx;
                f -= dx * 2;
            }

            y += sy;
            f += dy * 2;
        }
    }
    else
    {
        for (int32 i = 0; i < dx; i++)
        {
            canvas.setPixelColor(x, y, Qt::black);

            if (f > 0)
            {
                y += sy;
                f -= dx * 2;
            }

            x += sx;
            f += dy * 2;
        }
    }

    canvas.setPixelColor(x, y, Qt::black);
}


void CarcassRenderer::addLight(SharedLight)
{
}

void CarcassRenderer::setCamera(SharedCamera value)
{
    camera = value;
}

QImage CarcassRenderer::getRendered()
{
    auto toReturn = canvas;
    canvas.fill(Qt::white);
    return toReturn;
}

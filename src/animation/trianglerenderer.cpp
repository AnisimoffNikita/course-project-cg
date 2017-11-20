#include "trianglerenderer.h"

#include "commontransformation.h"

#include <QPainter>

TriangleRenderer::TriangleRenderer(double scale, int32 width, int32 height) :
    Renderer(scale, width, height),
    canvas(width, height, QImage::Format_ARGB32)
{
    canvas.fill(Qt::white);
}

TriangleRenderer::~TriangleRenderer()
{
}


void TriangleRenderer::renderMesh(const Mesh &mesh)
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

    auto qcolor = QColor(color.getRed(), color.getGreen(), color.getBlue());


    for (const auto& triangle : triangles)
    {
        Vertex v1 = vertices.at(triangle.v1());
        Vertex v2 = vertices.at(triangle.v2());
        Vertex v3 = vertices.at(triangle.v3());

        brezenhem(v1, v2);
        brezenhem(v2, v3);
        brezenhem(v3, v1);
    }

}


void TriangleRenderer::addLight(WeakLight)
{
}

void TriangleRenderer::setCamera(WeakCamera value)
{
    camera = value;
}

QPixmap TriangleRenderer::getRendered()
{
    auto toReturn = canvas;
    canvas.fill(Qt::white);
    return QPixmap::fromImage(toReturn);
}


void TriangleRenderer::brezenhem(const Vertex &p1, const Vertex &p2)
{
    int32 x1 = p1.getX(), y1 = p1.getY();
    int32 x2 = p2.getX(), y2 = p2.getY();
    if (x1 == x2 && y1 == y2)
    {
        canvas.setPixelColor(y1, x1, Qt::black);
    }
    int32 dx = x2 - x1, dy = y2 - y1;
    int32 sx = Math::sgn(dx), sy = Math::sgn(dy);
    dx = abs(dx); dy = abs(dy);
    bool flag = dy > dx;
    if (flag)
    {
        std::swap(dx, dy);
    }
    int32 f = (dy<<1) - dx;
    int32 x = x1, y = y1;

    if (flag)
    {
        for (int32 i = 0; i < dx; i++)
        {
            canvas.setPixelColor(x, y, Qt::black);
            if (f > 0)
            {
                x += sx;
                f -= dx*2;
            }
            y += sy;
            f += dy*2;
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
                f -= dx*2;
            }
            x += sx;
            f += dy*2;
        }
    }
    canvas.setPixelColor(x, y, Qt::black);
}



void TriangleRenderer::fillBottomFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{

}

void TriangleRenderer::fillTopFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{

}

void TriangleRenderer::fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{

}


#include "rendercontext.h"

#include "commontransformation.h"

#include <QPainter>

WeakCamera Render::getCamera() const
{
    return camera;
}

void Render::setCamera(const WeakCamera &value)
{
    camera = value;
}

QPixmap Render::getPixmap() const
{
    return pixmap;
}

void Render::setPixmap(const QPixmap &value)
{
    pixmap = value;
}

double Render::getScale() const
{
    return scale;
}

void Render::setScale(double value)
{
    scale = value;
}

void Render::renderMesh(const Mesh &mesh)
{
    if (camera.expired())
        return;

    auto workCamera = camera.lock();

    auto vertices = mesh.getVertices();
    auto edges = mesh.getEdges();

    CommonTransformation perspective(workCamera->getPVMatrix());

    QPainter *paint = new QPainter(&pixmap);
    paint->setPen(Qt::red);
    for (const auto& edge : edges)
    {
        Vertex v1 = vertices.at(edge.v1());
        Vertex v2 = vertices.at(edge.v2());
        perspective.transform(v1);
        perspective.transform(v2);
        v1 *= scale;
        v2 *= scale;
        v1 += Vertex(pixmap.width()/2, pixmap.height()/2, 0);
        v2 += Vertex(pixmap.width()/2, pixmap.height()/2, 0);
        paint->drawLine(v1.getX(), v1.getY(), v2.getX(), v2.getY());
    }
    delete paint;
}

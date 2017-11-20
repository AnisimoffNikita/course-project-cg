#include "carcassrenderer.h"

#include "commontransformation.h"

#include <QPainter>

CarcassRenderer::CarcassRenderer(double scale, int32 width, int32 height) :
    Renderer(scale, width, height),
    canvas(width, height)
{
    canvas.fill(Qt::white);
}


void CarcassRenderer::renderMesh(const Mesh &mesh)
{
    if (camera.expired())
        return;

    auto workCamera = camera.lock();

    auto vertices = mesh.getVertices();
    auto edges = mesh.getEdges();

    CommonTransformation perspective(workCamera->getPVMatrix());

    QPainter *paint = new QPainter(&canvas);
    paint->setPen(Qt::black);
    for (const auto& edge : edges)
    {
        Vertex v1 = vertices.at(edge.v1());
        Vertex v2 = vertices.at(edge.v2());
        perspective.transform(v1);
        perspective.transform(v2);
        v1 *= scale;
        v2 *= scale;
        v1 += Vertex(width/2, height/2, 0);
        v2 += Vertex(width/2, height/2, 0);
        paint->drawLine(v1.x(), v1.y(), v2.x(), v2.y());
    }
    delete paint;
}


void CarcassRenderer::addLight(WeakLight)
{
}

void CarcassRenderer::setCamera(WeakCamera value)
{
    camera = value;
}

QPixmap CarcassRenderer::getRendered()
{
    auto toReturn = canvas;
    canvas.fill(Qt::white);
    return toReturn;
}

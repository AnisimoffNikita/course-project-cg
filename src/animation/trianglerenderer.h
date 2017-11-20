#ifndef TRIANGLERENDERER_H
#define TRIANGLERENDERER_H


#include "renderer.h"

#include "zbuffer.h"
#include <QPixmap>

class TriangleRenderer : public Renderer
{
public:
    TriangleRenderer(double scale, int32 width, int32 height);
    virtual ~TriangleRenderer();

    virtual void setCamera(WeakCamera value) override;
    virtual void addLight(WeakLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QPixmap getRendered() override;

protected:
    void brezenhem(const Vertex &p1, const Vertex &p2);
    std::vector<int> getBrezenhemX(const Vertex &p1, const Vertex &p2);
    void setupBuffer();

    void fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);

    QImage canvas;
    ZBuffer buffer;
    WeakCamera camera;
    std::vector<WeakLight> lights;

};

#endif // TRIANGLERENDERER_H

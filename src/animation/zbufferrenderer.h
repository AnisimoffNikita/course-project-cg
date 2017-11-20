#ifndef ZBUFFERRENDERER_H
#define ZBUFFERRENDERER_H


#include "renderer.h"

#include "zbuffer.h"
#include <QPixmap>

class ZBufferRenderer : public Renderer
{
public:
    ZBufferRenderer(double scale, int32 width, int32 height);
    virtual ~ZBufferRenderer();

    virtual void setCamera(WeakCamera value) override;
    virtual void addLight(WeakLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QImage getRendered() override;

protected:
    void fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Color &color);
    std::vector<int> getBrezenhemX(const Vertex &p1, const Vertex &p2);
    void setupBuffer();

    ZBuffer buffer;
    WeakCamera camera;
    std::vector<WeakLight> lights;
};

#endif // ZBUFFER

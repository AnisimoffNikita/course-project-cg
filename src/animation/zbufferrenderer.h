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

    virtual void setCamera(SharedCamera value) override;
    virtual void addLight(SharedLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QImage getRendered() override;

protected:
    void putPixel(int x, int y, const Color &color);
    void fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
    void verticesSort(Vec3 &v1, Vec3 &v2, Vec3 &v3);

    std::vector<int> getBrezenhemX(const Vec3 &p1, const Vec3 &p2);
    void setupBuffer();

    ZBuffer buffer;
    SharedCamera camera;
    std::vector<SharedLight> lights;

    Mesh currentMesh;
};

#endif // ZBUFFER

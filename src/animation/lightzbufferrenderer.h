#ifndef LIGHTZBUFFERRENDERER_H
#define LIGHTZBUFFERRENDERER_H

#include "renderer.h"

#include "zbuffer.h"
#include <QPixmap>

class LightZBufferRenderer : public Renderer
{
public:
    LightZBufferRenderer(double scale, int32 width, int32 height);
    virtual ~LightZBufferRenderer();

    virtual void setCamera(SharedCamera value) override;
    virtual void addLight(SharedLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QImage getRendered() override;

protected:
    void fillTriangle(const Triangle &triangle);
    void triangleSort(const std::vector<Vertex> &vertices, Triangle &triangle);

    std::vector<int> getBrezenhemY(const Vertex &p1, const Vertex &p2);
    std::vector<Vertex> getNormals(const std::vector<int> &l, const Vertex &n1,
                                   const Vertex &n2);

    void setupBuffer();

    double calculateIntensity(const Vertex &n);

    ZBuffer buffer;
    SharedCamera camera;
    std::vector<SharedLight> lights;

    Mesh currentMesh;
    std::vector<Vertex> projected;
};


#endif // LIGHTZBUFFERRENDERER_H

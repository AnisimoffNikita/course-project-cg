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

    void putPixel(int x, int y, const Color &color);
    std::vector<int> getBrezenhemY(const Vec3 &p1, const Vec3 &p2);
    std::vector<Vec3> getNormals(const std::vector<int> &l, const Vec3 &n1,
                                 const Vec3 &n2);

    void setupBuffer();

    double calculateIntensity(const Vec3 &n);

    ZBuffer buffer;
    SharedCamera camera;
    std::vector<SharedLight> lights;

    Mesh currentMesh;
    std::vector<Vertex> projected;
};


#endif // LIGHTZBUFFERRENDERER_H

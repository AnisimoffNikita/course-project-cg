#ifndef CARCASSRENDERER_H
#define CARCASSRENDERER_H

#include "renderer.h"

#include <QPixmap>

class CarcassRenderer : public Renderer
{
public:
    CarcassRenderer(double scale, int32 width, int32 height);

    virtual void setCamera(SharedCamera value) override;
    virtual void addLight(SharedLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QImage getRendered() override;

protected:
    void putPixel(int x, int y, const Color &color);

    void brezenhem(const Vec3 &p1, const Vec3 &p2);


    SharedCamera camera;
    std::vector<SharedLight> lights;

};

#endif // CARCASSRENDERER_H

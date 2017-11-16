#ifndef CARCASSRENDERER_H
#define CARCASSRENDERER_H

#include "renderer.h"

#include <QPixmap>

class CarcassRenderer : public Renderer
{
public:
    CarcassRenderer(double scale, int32 width, int32 height);

    virtual void setCamera(WeakCamera value) override;
    virtual void addLight(WeakLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QPixmap getRendered() override;

protected:
    QPixmap canvas;
    WeakCamera camera;
    std::vector<WeakLight> lights;

};

#endif // CARCASSRENDERER_H

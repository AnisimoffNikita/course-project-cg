#ifndef RENDERER_H
#define RENDERER_H

#include "transformation.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"

#include <QPixmap>

class Renderer
{
public:
    Renderer(double scale, int32 width, int32 height);

    virtual void setCamera(WeakCamera value) = 0;
    virtual void addLight(WeakLight value) = 0;

    virtual void renderMesh(const Mesh &mesh) = 0;

    virtual QPixmap getRendered() = 0;

protected:
    double scale;
    int32 width;
    int32 height;
};

#endif // RENDERER_H

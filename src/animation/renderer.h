#ifndef RENDERER_H
#define RENDERER_H

#include "transformation.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"

#include <QImage>

class Renderer
{
public:
    Renderer(float scale, int width, int height);

    virtual void setCamera(SharedCamera value) = 0;
    virtual void addLight(SharedLight value) = 0;

    virtual void renderMesh(const Mesh &mesh) = 0;

    virtual QImage getRendered() = 0;


protected:

    float scale;
    int width;
    int height;
    QImage canvas;
};

#endif // RENDERER_H

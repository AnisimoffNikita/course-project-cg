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
    Renderer() = default;
    Renderer(float scale, int32 width, int32 height);

    virtual void setCamera(SharedCamera value) = 0;
    virtual void addLight(SharedLight value) = 0;

    virtual void start(int32 width, int32 height) = 0;

    virtual void renderMesh(shared_ptr<Mesh> mesh) = 0;

    virtual uchar *getRendered() = 0;

    virtual void finish() = 0;


protected:

    float scale;
    int32 width;
    int32 height;
};

#endif // RENDERER_H

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
    Renderer() = default;

    void setCamera(const WeakCamera &value);
    WeakCamera getCamera() const;

    void addLight(const Light &light);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    double getScale() const;
    void setScale(double value);

    virtual void renderMesh(const Mesh &mesh);


private:
    WeakCamera camera;
    QPixmap pixmap;
    double scale;
};

#endif // RENDERER_H

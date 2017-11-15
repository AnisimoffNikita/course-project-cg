#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include "transformation.h"
#include "camera.h"
#include "mesh.h"

#include <QPixmap>

class Render
{
public:
    Render() = default;

    void setCamera(const WeakCamera &value);
    WeakCamera getCamera() const;

    void renderMesh(const Mesh &mesh);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    double getScale() const;
    void setScale(double value);

private:
    WeakCamera camera;
    QPixmap pixmap;
    double scale;
};

#endif // RENDERCONTEXT_H

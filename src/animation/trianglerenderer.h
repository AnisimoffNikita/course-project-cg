#ifndef TRIANGLERENDERER_H
#define TRIANGLERENDERER_H


#include "renderer.h"

#include <QPixmap>

class TriangleRenderer : public Renderer
{
//public:
//    using Buffer = std::vector<std::vector<int32>>;
public:
    TriangleRenderer(double scale, int32 width, int32 height);
    virtual ~TriangleRenderer();

    virtual void setCamera(WeakCamera value) override;
    virtual void addLight(WeakLight) override;

    virtual void renderMesh(const Mesh &mesh) override;

    virtual QPixmap getRendered() override;

protected:
    void brezenhem(const Vertex &p1, const Vertex &p2);
    void setupBuffer();

    void drawHorizontLine(int32 x1, int32 x2, int32 y, uint32 z1, uint32 z2);
    void fillBottomFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
    void fillTopFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
    void fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);

    QImage canvas;
    //Buffer buffer;
    WeakCamera camera;
    std::vector<WeakLight> lights;

};

#endif // TRIANGLERENDERER_H

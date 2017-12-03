#ifndef LIGHTZBUFFERRENDERER_H
#define LIGHTZBUFFERRENDERER_H

#include "renderer.h"
#include "src/number.h"
#include "zbuffer.h"
#include <QPixmap>

class LightZBufferRenderer : public Renderer
{
public:
    LightZBufferRenderer() = default;
    LightZBufferRenderer(float scale, int32 width, int32 height);
    virtual ~LightZBufferRenderer();

    virtual void setCamera(SharedCamera value) override;
    virtual void addLight(SharedLight) override;

    virtual void start(int32 width, int32 height) override;
    virtual void renderMesh(shared_ptr<Mesh> mesh) override;

    virtual uchar *getRendered() override;
    virtual void finish() override;

protected:
    void fillTriangle(Triangle &triangle);
    void getLeftRightBounds(std::vector<float> &lleft, std::vector<float> &lright,
                            std::vector<Vec3> &nleft, std::vector<Vec3> &nright, std::vector<float> &zleft,
                            std::vector<float> &zright,
                            Triangle &triangle,
                            bool &swapped);
    void triangleSort(const std::vector<Vec3> &vertices, Triangle &triangle);
    Color calculateIntensity(const Vec3 &n, const Vec3 &orig, const Color &ka,
                             const Color &kd, const Color &ks, float ns);

    void putPixel(int32 x, int32 y, const Color &color);
    std::vector<float> getBrezenhemX(const Vec3 &p1, const Vec3 &p2);
    std::vector<Vec3> getNormals(const std::vector<float> &l, const Vec3 &n1,
                                 const Vec3 &n2);
    std::vector<float> getZLine(const Vec3 &p1, const Vec3 &p2, int32 n);

    ZBuffer zbuffer;
    uchar *buffer;
    SharedCamera camera;

    vector<SharedLight> lights;

    vector<shared_ptr<Mesh>> meshes;
    shared_ptr<Mesh> currentMesh;
    vector<Vec3> projected;
};


#endif // LIGHTZBUFFERRENDERER_H

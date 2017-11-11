#ifndef MODEL_H
#define MODEL_H

#include "src/animation/sceneobject.h"
#include "src/animation/mesh.h"
#include "src/animation/transformation.h"

class Model : public SceneObject
{
public:
    Model();
    virtual ~Model();

    virtual void draw(const RenderContext &render) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;
private:
    Mesh _mesh;
};

#endif // MODEL_H

#ifndef MODEL_H
#define MODEL_H

#include "src/animation/sceneobject.h"
#include "src/animation/mesh.h"
#include "src/animation/transformation.h"

class Model : public SceneObject
{

public:
    Model() = default;
    Model(const Vertex &position, const Mesh &mesh);
    virtual ~Model() = default;

    virtual void draw(Renderer &render) override;
    virtual void transform(const Transformation &transformation) override;
    virtual bool isCamera() override;
    virtual bool isLight() override;

    Mesh getMesh() const;
    void setMesh(const Mesh &mesh);

private:
    Mesh mesh;
};

using SharedModel = std::shared_ptr<Model>;

#endif // MODEL_H

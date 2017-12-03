#include "model.h"

#include "renderer.h"
#include "movetransformation.h"

Model::Model(const Vec3 &position, const Mesh &mesh)
    : SceneObject(position)
    , mesh(mesh)
{
}

void Model::draw(std::unique_ptr<Renderer> &renderer)
{
    auto meshToRender = make_shared<Mesh>(mesh);
    meshToRender->transform(MoveTransformation(position));
    renderer->renderMesh(meshToRender);
}

void Model::transform(Transformation &transformation)
{
    transformation.transform(position);
    transformation.resetOrigin();
    mesh.transform(transformation);
}

bool Model::isCamera()
{
    return false;
}

bool Model::isLight()
{
    return false;
}

Mesh Model::getMesh() const
{
    return mesh;
}

void Model::setMesh(const Mesh &mesh)
{
    this->mesh = mesh;
}

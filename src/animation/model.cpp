#include "model.h"

#include "renderer.h"


Model::Model(const Vertex &position, const Mesh &mesh) :
    SceneObject(position),
    mesh(mesh)
{
}

void Model::draw(Renderer &render)
{
    render.renderMesh(mesh);
}

void Model::transform(const Transformation &transformation)
{
    transformation.transform(position);
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

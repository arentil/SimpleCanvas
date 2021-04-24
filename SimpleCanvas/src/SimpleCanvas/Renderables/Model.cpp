#include "Model.h"

namespace sc
{
Model::Model(std::vector<BaseMeshPtr> const meshes)
: _meshes(meshes)
{}

void Model::draw(Shader const& shader, Camera const& camera, Material const& material, scmath::Mat4 const& modelMatrix) const
{
    for (BaseMeshPtr const& mesh : _meshes)
    {
        mesh->draw(shader, camera, material, modelMatrix);
    }
}
} // namespace sc
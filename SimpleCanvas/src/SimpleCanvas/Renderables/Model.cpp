#include "Model.h"

namespace sc
{
Model::Model(std::vector<BaseMeshPtr> const& meshes)
: _meshes(meshes)
{}

void Model::draw(Shader const& shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{
    for (BaseMeshPtr const& mesh : _meshes)
    {
        mesh->draw(shader, camera, lights, modelMatrix);
    }
}
} // namespace sc
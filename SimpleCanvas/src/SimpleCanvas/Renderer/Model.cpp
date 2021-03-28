#include "Model.h"

namespace sc
{
Model::Model(std::vector<Mesh> const meshes)
: _meshes(meshes)
{
    
}

void Model::draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const
{
    for (Mesh const& mesh : _meshes)
    {
        mesh.draw(shader, camera, modelMatrix);
    }
}
} // namespace sc
#pragma once

#include "Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

#include <SCMath.h>

#include <vector>

namespace sc
{
class Model
{
public:
    Model(std::vector<Mesh> const meshes);
    ~Model() = default;

    void draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const;

private:
    std::vector<Mesh> const _meshes;
};
} // namespace sc
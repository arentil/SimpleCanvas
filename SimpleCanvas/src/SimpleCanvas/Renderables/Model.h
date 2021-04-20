#pragma once

#include "BaseMesh.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

#include <SCMath.h>

#include <vector>

namespace sc
{
class Model
{
public:
    Model(std::vector<BaseMeshPtr> const meshes);
    ~Model() = default;

    void draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const;

private:
    std::vector<BaseMeshPtr> const _meshes;
};
} // namespace sc
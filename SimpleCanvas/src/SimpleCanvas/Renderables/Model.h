#pragma once

#include "BaseMesh.h"
#include "Renderer/Shader.h"
#include "Camera/FPSCamera.h"
#include "Renderables/Lights.h"

#include <SCMath.h>

#include <vector>

namespace sc
{
class Model;
using ModelPtr = std::shared_ptr<Model>;

class Model
{
public:
    Model() = default;
    Model(std::vector<BaseMeshPtr> const& meshes);
    ~Model() = default;

    void draw(Shader const& shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const;

private:
    std::vector<BaseMeshPtr> const _meshes;
};
} // namespace sc
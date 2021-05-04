#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Camera/FPSCamera.h"
#include "Renderables/AABB.h"
#include "Renderables/Lights.h"

namespace sc
{
class BaseMesh;
using BaseMeshPtr = std::shared_ptr<BaseMesh>;

class BaseMesh
{
public:
    virtual ~BaseMesh() = default;
    virtual void draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const = 0;

protected:
    AABB _aabb;
    uint32_t VAO, VBO;
};
} // namespace sc
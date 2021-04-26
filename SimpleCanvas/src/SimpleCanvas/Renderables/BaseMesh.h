#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Lights.h"

namespace sc
{
class BaseMesh;
using BaseMeshPtr = std::shared_ptr<BaseMesh>;

class BaseMesh
{
public:
    virtual ~BaseMesh() = default;
    virtual void draw(Shader const& shader, Camera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const = 0;

protected:
    uint32_t VAO, VBO;
};
} // namespace sc
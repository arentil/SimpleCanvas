#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Camera/CameraController.h"
#include "ObjectLogic/AABB.h"
#include "ObjectLogic/Lights.h"

namespace sc
{
class BaseMesh;
using BaseMeshPtr = std::shared_ptr<BaseMesh>;

class BaseMesh
{
public:
    BaseMesh(size_t numberOfVertices);
    virtual ~BaseMesh() = default;
    
    virtual void draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix) = 0;
    virtual AABB getAABB() const { return aabb; }
    virtual void updateAABB(scmath::Mat4 const& modelMatrix);

protected:
    BoundingBox bb; // original 8 vertices, do not use!
    AABB aabb;
    uint32_t VAO;
    const size_t verticesCount;
};
} // namespace sc
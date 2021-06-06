#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Tools/FileReader.h"
#include "BoundingBox.h"

namespace sc
{
class FPSCamera;

class AABB
{
public:
    AABB() = default;
    AABB(scmath::Vec3 const& min, scmath::Vec3 const& max);
    virtual ~AABB() = default;

    bool isCollision(AABB const& other) const;

    // for test/debug purpose only!
    void initDebugShader();
    // for test/debug purpose only!
    void draw(FPSCamera const& camera, scmath::Mat4 const& modelMatrix) const;

    // for frustum culling check
    scmath::Vec3 getVertexP(scmath::Vec3 const& normal) const;

    BoundingBox bb;
    ShaderPtr debugShader;
};
} // namespace sc
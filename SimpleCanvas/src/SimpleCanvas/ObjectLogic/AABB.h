#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Tools/FileReader.h"
#include "BoundingBox.h"

namespace sc
{
enum class CollisionDir
{
    NONE,
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    TOP,
    BOTTOM
};

class CameraController;

class AABB
{
public:
    AABB() = default;
    AABB(scmath::Vec3 const& min, scmath::Vec3 const& max);
    virtual ~AABB() = default;

    std::pair<bool, CollisionDir> getCollision(AABB const& other) const;
    CollisionDir getDirection(AABB const& other) const;
    static CollisionDir getOppositeDirection(CollisionDir direction);

    // for test/debug purpose only!
    void initDebugShader();
    // for test/debug purpose only!
    void draw(CameraController const& camCtrl, scmath::Mat4 const& modelMatrix) const;

    // for frustum culling check
    scmath::Vec3 getVertexP(scmath::Vec3 const& normal) const;

    BoundingBox bb;
    ShaderPtr debugShader;
};
} // namespace sc
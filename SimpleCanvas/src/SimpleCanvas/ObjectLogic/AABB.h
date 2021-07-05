#pragma once

#include <SCMath.h>

#include "Renderer/Shader.h"
#include "Tools/FileReader.h"
#include "BoundingBox.h"

namespace sc
{
enum class CollisionSide
{
    UNDEFINED,
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

std::map<CollisionSide, CollisionSide> const opposideDirectionMap
{
    {CollisionSide::UNDEFINED, CollisionSide::UNDEFINED},
    {CollisionSide::FRONT, CollisionSide::BACK},
    {CollisionSide::BACK, CollisionSide::FRONT},
    {CollisionSide::LEFT, CollisionSide::RIGHT},
    {CollisionSide::RIGHT, CollisionSide::LEFT},
    {CollisionSide::UP, CollisionSide::DOWN},
    {CollisionSide::DOWN, CollisionSide::UP}
};

class CameraController;

class AABB
{
public:
    AABB() = default;
    AABB(scmath::Vec3 const& min, scmath::Vec3 const& max);
    virtual ~AABB() = default;

    std::pair<bool, CollisionSide> getCollision(AABB const& other) const;
    CollisionSide getCollisionSide(AABB const& other) const;
    static CollisionSide getOpposideSide(CollisionSide side);

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
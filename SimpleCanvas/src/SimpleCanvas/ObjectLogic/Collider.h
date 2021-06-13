#pragma once

namespace sc
{
enum class ColliderType
{
    SPHERE,
    AABB
};

class Collider
{
public:
    Collider(ColliderType colliderType) : type(colliderType) {}
    virtual ~Collider() = default;

    ColliderType getType() const { return type; }
    virtual bool isCollision(Collider const& other) const = 0;

protected:
    ColliderType type;
};
} // namespace sc
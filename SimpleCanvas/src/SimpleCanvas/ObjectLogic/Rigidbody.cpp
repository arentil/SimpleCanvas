#include "Rigidbody.h"

namespace sc
{
Rigidbody::Rigidbody(scmath::Vec3 const& aabbMin, scmath::Vec3 const& aabbMax)
: aabb(aabbMin, aabbMax)
{}
} // namespace sc
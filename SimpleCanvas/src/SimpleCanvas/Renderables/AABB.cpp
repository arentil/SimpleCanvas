#include "AABB.h"

namespace sc
{
namespace
{
bool isInRange(float min, float value, float max)
{
    return min < value && value < max;
}
} // namespace

AABB::AABB(scmath::Vec3 const& min, scmath::Vec3 const& max)
: _min(min), _max(max)
{}

void AABB::setMinMax(scmath::Vec3 const& min, scmath::Vec3 const& max) 
{
    _min = min;
    _max = max;
}

bool AABB::isInFrustrum(Camera const& camera, scmath::Mat4 const& modelMatrix) const
{
    const auto MVP = camera.getViewProjMatrix() * modelMatrix;
    std::vector<scmath::Vec4> const corners
    {
        {_min.x, _min.y, _min.z, 1.0f}, // x y z
        {_max.x, _min.y, _min.z, 1.0f}, // X y z
        {_min.x, _max.y, _min.z, 1.0f}, // x Y z
        {_max.x, _max.y, _min.z, 1.0f}, // X Y z

        {_min.x, _min.y, _max.z, 1.0f}, // x y Z
        {_max.x, _min.y, _max.z, 1.0f}, // X y Z
        {_min.x, _max.y, _max.z, 1.0f}, // x Y Z
        {_max.x, _max.y, _max.z, 1.0f}, // X Y Z
    };

    bool inside = false;

    for (auto const& corner : corners)
    {
        scmath::Vec4 const mvpCorner = MVP * corner;
        inside = inside ||
            isInRange(-mvpCorner.w, mvpCorner.x, mvpCorner.w) &&
            isInRange(-mvpCorner.w, mvpCorner.y, mvpCorner.w) &&
            isInRange(0.0f, mvpCorner.z, mvpCorner.w);
    }

    return inside;
}
} // namespace sc
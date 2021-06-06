#include "BoundingBox.h"

namespace sc
{
BoundingBox::BoundingBox(scmath::Vec3 const& minV, scmath::Vec3 const& maxV) 
: min(minV), max(maxV)
{
    
}

void BoundingBox::setMinMax(scmath::Vec3 const& minV, scmath::Vec3 const& maxV) 
{
    min = minV;
    max = maxV;
}

std::vector<scmath::Vec3> BoundingBox::get8Corners() const
{
    return
    {
        min, // min.x, min.y, min.z
        max, // max.x, max.y, max.z
        {min.x, max.y, max.z},
        {min.x, max.y, min.z},
        {max.x, max.y, min.z},
        {max.x, min.y, min.z},
        {max.x, min.y, max.z},
        {min.x, min.y, max.z},
    };
}
}
#pragma once

namespace sc
{
using Corners = std::vector<scmath::Vec3>;
class BoundingBox
{
public:
    BoundingBox() = default;
    BoundingBox(scmath::Vec3 const& minV, scmath::Vec3 const& maxV);
    virtual ~BoundingBox() = default;

    void setMinMax(scmath::Vec3 const& minV, scmath::Vec3 const& maxV);
    Corners get8Corners() const;

    scmath::Vec3 min;
    scmath::Vec3 max;
};
} // namespace sc
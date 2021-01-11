#pragma once

#include "Vec3.h"

namespace scmath
{
class Vec4;
class Mat4;

// q = w + xi + yj + zk
class Quat
{
public:
    Quat() = default;
    Quat(float wP, Vec3 const& vP);
    Quat(float wP, float x, float y, float z);


    Quat operator+(Quat const& other) const;
    Quat operator-(Quat const& other) const;
    Quat operator-() const;
    Quat operator*(Quat const& other) const;
    Quat operator*(float multiplier) const;
    Quat operator/(float multiplier) const;
    operator Vec4() const;

    // quaternion must be normalized
    Mat4 asMatrix() const;

    // length??
    float magnitude() const;

    Quat normalized() const;


    float w;
    Vec3 v;
};
} // namespace scmath
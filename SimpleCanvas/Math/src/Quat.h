#pragma once

#include "Vec3.h"
#include "Mat4.h"

namespace scmath
{
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
    float operator[](int i) const;

    // quaternion must be normalized
    Mat4 asMatrix() const;

    // length??
    float magnitude() const;

    Quat normalized() const;


    union
    {
        struct 
        {
            Vec3 v;
            float w;
        };
        float arr[4];
    };
};
} // namespace scmath
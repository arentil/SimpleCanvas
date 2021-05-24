#include "Quat.h"

#include <cmath>

#include "Vec4.h"
#include "Mat4.h"
#include "Utility.h"

namespace scmath
{
Quat::Quat(float wP, Vec3 const& vP)
: w(wP), v(vP)
{}

Quat::Quat(float wP, float x, float y, float z)
: w(wP), v(x, y, z)
{}

Quat Quat::operator+(Quat const& other) const
{
    return Quat(w + other.w, v + other.v);
}

Quat Quat::operator-(Quat const& other) const
{
    return Quat(w - other.w, v - other.v);
}

Quat Quat::operator-() const
{
    return Quat(-w, -v);
}

Quat Quat::operator*(Quat const& other) const
{
    return Quat(
        w * other.w - v.x * other.v.x - v.y * other.v.y - v.z * other.v.z,
        w * other.v.x + v.x * other.w + v.y * other.v.z - v.z * other.v.y,
        w * other.v.y - v.x * other.v.z + v.y * other.w + v.z * other.v.x,
        w * other.v.z + v.x * other.v.y - v.y * other.v.x + v.z * other.w
    );
}

Quat Quat::operator*(float multiplier) const
{
    return Quat(w * multiplier, v * multiplier);
}

Quat Quat::operator/(float multiplier) const
{
    return Quat(w / multiplier, v / multiplier);
}

Quat::operator Vec4() const
{
    return Vec4(v, w);
}

Quat Quat::conjugate() const
{
    return {w, -v};
}

Quat Quat::inverse() const
{
    return conjugate().normalized();
}

Mat4 Quat::rotationMatrix() const
{
    float const xx = v.x * v.x;
    float const xy = v.x * v.y;
    float const xz = v.x * v.z;
    float const xw = v.x * w;

    float const yy = v.y * v.y;
    float const yz = v.y * v.z;
    float const yw = v.y * w;

    float const zz = v.z * v.z;
    float const zw = v.z * w;

    return Mat4(
        {1.0f - 2.0f * (yy + zz), 2.0f * (xy + zw), 2.0f * (xz - yw), 0.0f},
        {2.0f * (xy - zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + xw), 0.0f},
        {2.0f * (xz + yw), 2.0f * (yz - xw), 1.0f - 2.0f * (xx + yy), 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    );
}

float Quat::magnitude() const
{
    return std::sqrt(w * w + v.x * v.x + v.y * v.y + v.z * v.z);
}

Quat Quat::normalized() const
{
    return *this / magnitude();
}

Quat Quat::identity() 
{
    return Quat(1.0f, Vec3(0.0f, 0.0f, 0.0f));
}

Quat Quat::eulerToQuat(float roll, float pitch, float yaw)
{
    float cy = std::cos(yaw / 2.0f);
    float cp = std::cos(pitch / 2.0f);
    float cr = std::cos(roll / 2.0f);
    float sy = std::sin(yaw / 2.0f);
    float sp = std::sin(pitch / 2.0f);
    float sr = std::sin(roll / 2.0f);

    float cpcy = cp * cy;
    float spsy = sp * sy;

    return Quat(cr * cpcy + sr * spsy,              // w
                Vec3(sr * cpcy - cr * spsy,         // x
                     cr * sp * cy + sr * cp * sy,   // y
                     cr * cp * sy - sr * sp * cy))  // z
            .normalized();
}

Quat Quat::eulerToQuat(Vec3 const& v) 
{
    return Quat::eulerToQuat(v.x, v.y, v.z);
}

Quat Quat::slerp(Quat const& from, Quat const& target, float t)
{
    float to1[4];
    float omega, cosom, sinom, scale0, scale1;
    cosom = from.v.x * target.v.x + from.v.y * target.v.y + from.v.z * target.v.z + from.w * target.w;

    // adjust signs (if necessary)
    if (cosom < 0.0f)
    {
        cosom = -cosom;
        to1[0] = -target.v.x;
        to1[1] = -target.v.y;
        to1[2] = -target.v.z;
        to1[3] = -target.w;
    }
    else
    {
        to1[0] = target.v.x;
        to1[1] = target.v.y;
        to1[2] = target.v.z;
        to1[3] = target.w;
    }

    // calculate coefficients
    if ((1.0f - cosom) > 0.001f)
    {
        // standard case (slerp)
        omega = std::acos(cosom);
        sinom = std::sin(omega);
        scale0 = std::sin((1.0f - t) * omega) / sinom;
        scale1 = std::sin(t * omega) / sinom;
    }
    else
    {
        // from(this) and to(target) quaternions are very close
        // .. so we can do a linear interpolation
        scale0 = 1.0f - t;
        scale1 = t;
    }

    return Quat(scale0 * from.w + scale1 * to1[3],
                Vec3(
                    scale0 * from.v.x + scale1 * to1[0],
                    scale0 * from.v.y + scale1 * to1[1],
                    scale0 * from.v.z + scale1 * to1[2]
                ));
}
} // namespace scmath

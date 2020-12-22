#include "Quat.h"

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

float Quat::operator[](int i) const
{

    return arr[i];
}

Mat4 Quat::asMatrix() const
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
        {1 - 2 * (yy * zz), 2 * (xy + zw), 2 * (xz - yw), 0},
        {2 * (xy - zw), 1 - 2 * (xx + zz), w * (yz + xw), 0},
        {2 * (xz + yw), 2 * (yz - xw), 1 - 2 * (xx + yy), 0},
        {0, 0, 0, 1}
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
} // namespace scmath
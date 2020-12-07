#include "Vec3.h"

#include <utility>
#include <cmath>
#include <cassert>

#include "Utility.h"

namespace scmath 
{
Vec3::Vec3(float pX, float pY, float pZ)
 : x(pX), y(pY), z(pZ)
{}

Vec3::Vec3(Vec3 const& other)
 : x(other.x), y(other.y), z(other.z)
{}

float Vec3::dot(Vec3 const& other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

Vec3 Vec3::cross(Vec3 const& other) const
{
    Vec3 result(
        (y * other.z) - (z * other.y),
        (z * other.x) - (x * other.z),
        (x * other.y) - (y * other.x));
    return std::move(result);
}

Vec3& Vec3::operator=(Vec3 const& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vec3 Vec3::operator+(Vec3 const& other) const
{
    Vec3 result(x + other.x, y + other.y, z + other.z);
    return std::move(result);
}

Vec3 Vec3::operator-(Vec3 const& other) const
{
    Vec3 result(x - other.x, y - other.y, z - other.z);
    return std::move(result);
}

bool Vec3::operator==(Vec3 const& other) const
{
    return equal(x, other.x) && equal(y, other.y) && equal(z, other.z);
}

Vec3 Vec3::operator*(float multiplier) const
{
    Vec3 result(x * multiplier, y * multiplier, z * multiplier);
    return std::move(result);
}

Vec3 Vec3::operator*(int multiplier) const
{
    return std::move((this->operator*((float)multiplier)));
}

Vec3 Vec3::operator*(Vec3 const& other) const
{
    Vec3 result(x * other.x, y * other.y, z * other.z);
    return result;
}

Vec3 Vec3::operator/(float divider) const
{
    assert(divider != 0.0f);
    Vec3 result(x / divider, y / divider, z / divider);
    return std::move(result);
}

Vec3 Vec3::operator/(int divider) const
{
    return std::move(this->operator/((float)divider));
}

float Vec3::length() const
{
    return std::sqrt((x * x) + (y * y) + (z * z));
}

Vec3 Vec3::normalized() const
{
    assert(!isZero());
    return *this / this->length();
}

bool Vec3::isZero() const
{
    return (x == 0.0f && y == 0.0f && z == 0.0f);
}

// ----- static methods -----

float Vec3::dot(Vec3 const& v1, Vec3 const& v2)
{
    return v1.dot(v2);
}

Vec3 Vec3::cross(Vec3 const& v1, Vec3 const& v2)
{
    return std::move(v1.cross(v2));
}

Vec3 Vec3::projection(Vec3 const& v, Vec3 const& onNormal)
{
    assert(!onNormal.isZero());
    Vec3 result = (v.dot(onNormal) / square(onNormal.length())) * onNormal;
    return std::move(result);
}

Vec3 Vec3::perpendicular(Vec3 const& v, Vec3 const& onVector)
{
    return (v - Vec3::projection(v, onVector));
}

// ******************
//      FRIENDS
// ******************
std::ostream & operator<<(std::ostream &os, scmath::Vec3 const& v)
{
    os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::ostream & operator<<(scmath::Vec3 const& v, std::ostream &os)
{
    os << v;
    return os;
}

Vec3 operator*(float multiplier, Vec3 const& v)
{
    Vec3 result(multiplier * v.x, multiplier * v.y, multiplier * v.z);
    return result;
}
} // namespace scmath
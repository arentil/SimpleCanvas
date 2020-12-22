#include "Vec3.h"

#include <utility>
#include <cmath>
#include <cassert>
#include <string>

#include "Utility.h"

namespace scmath 
{
Vec3::Vec3(float pX, float pY, float pZ)
 : x(pX), y(pY), z(pZ)
{}

Vec3::Vec3(Vec3 const& other)
 : x(other.x), y(other.y), z(other.z)
{}

Vec3::Vec3(Vec3 && other) : Vec3(other)
{
    other.x = other.y = other.z = 0.0f;
}

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

float Vec3::distance(Vec3 const& other) const
{
    return (other - *this).length();
}

Vec3 Vec3::reflect(Vec3 const& normal) const
{
    Vec3 result = *this - (this->dot(2.0f * normal) * normal);
    return result;
}

Vec3 Vec3::refract(Vec3 const& normal, float factor) const
{
    Vec3 const& thisNorm = normalized();
    float const NdotThis = normal.dot(thisNorm);
    float k = 1.0f - square(factor) * (1.0f - square(NdotThis));
    if (k < 0)
        return Vec3();
    
    Vec3 result = factor * thisNorm - ((factor * NdotThis + std::sqrt(k)) * normal);
    return result;
}

std::string Vec3::to_string() const
{
    std::string result = "Vec3(";
    result += std::to_string(x) + ", ";
    result += std::to_string(y) + ", ";
    result += std::to_string(z) + ")";
    return result;
}

// ----- operators -----
Vec3& Vec3::operator=(Vec3&& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    other.x = other.y = other.z = 0.0f;
    return *this;
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
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator+(float num) const
{
    return Vec3(x + num, y + num, z + num);
}

Vec3 Vec3::operator-(Vec3 const& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator-() const
{
    return *this * (-1);
}

bool Vec3::operator==(Vec3 const& other) const
{
    return f_equal(x, other.x) && f_equal(y, other.y) && f_equal(z, other.z);
}

bool Vec3::operator!=(Vec3 const& other) const
{
    return !(this->operator==(other));
}

Vec3 Vec3::operator*(float multiplier) const
{
    return Vec3(x * multiplier, y * multiplier, z * multiplier);
}

Vec3 Vec3::operator/(float divider) const
{
    assert(divider != 0.0f);
    return Vec3(x / divider, y / divider, z / divider);
}

float Vec3::operator[](int i) const
{
    assert(i < 3 && i >= 0);
    return arr[i];
}

float& Vec3::operator[](int i)
{
    assert(i < 3 && i >= 0);
    return arr[i];
}

Vec3::operator float *()
{
    return arr;
}

// ----- static methods -----
float Vec3::dot(Vec3 const& v1, Vec3 const& v2)
{
    return v1.dot(v2);
}

Vec3 Vec3::cross(Vec3 const& v1, Vec3 const& v2)
{
    return v1.cross(v2);
}

Vec3 Vec3::projection(Vec3 const& v, Vec3 const& onNormal)
{
    assert(!onNormal.isZero());
    return Vec3((v.dot(onNormal) / square(onNormal.length())) * onNormal);
}

Vec3 Vec3::perpendicular(Vec3 const& v, Vec3 const& onVector)
{
    return (v - Vec3::projection(v, onVector));
}

Vec3 Vec3::reflect(Vec3 const& in, Vec3 const& normal)
{
    return in.reflect(normal);
}

Vec3 Vec3::refract(Vec3 const& in, Vec3 const& normal, float factor)
{
    return in.refract(normal, factor);
}

Vec3 Vec3::distance(Vec3 const& first, Vec3 const& second)
{
    return first.distance(second);
}

// ----- friends -----
std::ostream & operator<<(std::ostream &os, scmath::Vec3 const& v)
{
    os << v.to_string();
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
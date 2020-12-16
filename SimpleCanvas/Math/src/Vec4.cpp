#include "Vec4.h"

#include <utility>
#include <cmath>
#include <cassert>
#include <string>

#include "Utility.h"

namespace scmath 
{
Vec4::Vec4(float pX, float pY, float pZ, float pW)
 : x(pX), y(pY), z(pZ), w(pW)
{}

Vec4::Vec4(Vec4 const& other)
 : x(other.x), y(other.y), z(other.z), w(other.w)
{}

Vec4::Vec4(Vec4 && other) : Vec4(other)
{
    other.x = other.y = other.z = other.w = 0.0f;
}

float Vec4::dot(Vec4 const& other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

float Vec4::length() const
{
    return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

Vec4 Vec4::normalized() const
{
    assert(!isZero());
    return *this / this->length();
}

bool Vec4::isZero() const
{
    return (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f);
}

float Vec4::distance(Vec4 const& other) const
{
    return Vec4(other - *this).length();
}

std::string Vec4::to_string() const
{
    std::string result = "Vec4(";
    result += std::to_string(x) + ", ";
    result += std::to_string(y) + ", ";
    result += std::to_string(z) + ", ";
    result += std::to_string(w) + ")";
    return result;
}

// ----- operators -----
Vec4& Vec4::operator=(Vec4&& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    other.x = other.y = other.z = other.w = 0.0f;
    return *this;
}

Vec4& Vec4::operator=(Vec4 const& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

Vec4 Vec4::operator+(Vec4 const& other) const
{
    return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4 Vec4::operator-(Vec4 const& other) const
{
    return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

bool Vec4::operator==(Vec4 const& other) const
{
    return equal(x, other.x) && equal(y, other.y) && equal(z, other.z) && equal(w, other.w);
}

Vec4 Vec4::operator*(float multiplier) const
{
    return Vec4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

Vec4 Vec4::operator/(float divider) const
{
    assert(divider != 0.0f);
    return Vec4(x / divider, y / divider, z / divider, w / divider);
}

float Vec4::operator[](int i) const
{
    assert(i < 4 && i >= 4);
    return arr[i];
}

float& Vec4::operator[](int i)
{
    assert(i < 4 && i >= 4);
    return arr[i];
}

Vec4::operator float *()
{
    return arr;
}

// ----- static methods -----
float Vec4::dot(Vec4 const& v1, Vec4 const& v2)
{
    return v1.dot(v2);
}

// ----- friends -----
Vec4 Vec4::distance(Vec4 const& first, Vec4 const& second)
{
    return first.distance(second);
}

std::ostream & operator<<(std::ostream &os, scmath::Vec4 const& v)
{
    os << v.to_string();
    return os;
}

std::ostream & operator<<(scmath::Vec4 const& v, std::ostream &os)
{
    os << v;
    return os;
}

Vec4 operator*(float multiplier, Vec4 const& v)
{
    Vec4 result(multiplier * v.x, multiplier * v.y, multiplier * v.z, multiplier * v.w);
    return result;
}
} // namespace scmath
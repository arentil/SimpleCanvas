#include "Vec2.h"

#include <utility>
#include <cmath>
#include <cassert>
#include <string>

#include "Utility.h"

namespace scmath
{
Vec2::Vec2(float pX, float pY)
 : x(pX), y(pY)
{}

Vec2::Vec2(Vec2 const& other)
: x(other.x), y(other.y)
{}

Vec2::Vec2(Vec2&& other) : Vec2(other)
{
    other.x = other.y = 0.0f;
}

float Vec2::dot(Vec2 const& other) const
{
    return (x * other.x) + (y * other.y);
}

float Vec2::length() const
{
    return std::sqrt((x * x) + (y * y));
}

Vec2 Vec2::normalized() const
{
    assert(!isZero());
    return *this / this->length();
}

bool Vec2::isZero() const
{
    return (x == 0.0f && y == 0.0f);
}

float Vec2::distance(Vec2 const& other) const
{
    return Vec2(other - *this).length();
}

Vec2 Vec2::reflect(Vec2 const& normal) const
{
    Vec2 result = *this - (this->dot(2.0f * normal) * normal);
    return result;
}

Vec2 Vec2::refract(Vec2 const& normal, float factor) const
{
    Vec2 const& thisNorm = normalized();
    float const NdotThis = normal.dot(thisNorm);
    float k = 1.0f - square(factor) * (1.0f - square(NdotThis));
    if (k < 0)
        return Vec2();
    
    Vec2 result = factor * thisNorm - ((factor * NdotThis + std::sqrt(k)) * normal);
    return result;
}

std::string Vec2::to_string() const
{
    std::string result = "Vec2(";
    result += std::to_string(x) + ", ";
    result += std::to_string(y) + ")";
    return result;
}

Vec2& Vec2::operator=(Vec2&& other)
{
    x = other.x;
    y = other.y;
    other.x = other.y = 0.0f;
    return *this;
}

Vec2& Vec2::operator=(Vec2 const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

Vec2 Vec2::operator+(Vec2 const& other) const
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(Vec2 const& other) const
{
    return Vec2(x - other.x, y - other.y);
}

bool Vec2::operator==(Vec2 const& other) const
{
    return equal(x, other.x) && equal(y, other.y);
}

Vec2 Vec2::operator*(float multiplier) const
{
    return Vec2(x * multiplier, y * multiplier);
}

Vec2 Vec2::operator/(float divider) const
{
    assert(divider != 0.0f);
    return Vec2(x / divider, y / divider);
}

// ----- static methods -----
float Vec2::dot(Vec2 const& v1, Vec2 const& v2)
{
    return v1.dot(v2);
}

Vec2 Vec2::projection(Vec2 const& v, Vec2 const& onNormal)
{
    assert(!onNormal.isZero());
    return Vec2((v.dot(onNormal) / square(onNormal.length())) * onNormal);
}

Vec2 Vec2::perpendicular(Vec2 const& v, Vec2 const& onVector)
{
    return (v - Vec2::projection(v, onVector));
}

Vec2 Vec2::reflect(Vec2 const& in, Vec2 const& normal)
{
    return in.reflect(normal);
}

Vec2 Vec2::refract(Vec2 const& in, Vec2 const& normal, float factor)
{
    return in.refract(normal, factor);
}

Vec2 Vec2::distance(Vec2 const& first, Vec2 const& second)
{
    return first.distance(second);
}

// ----- friends -----
std::ostream & operator<<(std::ostream &os, scmath::Vec2 const& v)
{
    os << v.to_string();
    return os;
}

std::ostream & operator<<(scmath::Vec2 const& v, std::ostream &os)
{
    os << v;
    return os;
}

Vec2 operator*(float multiplier, Vec2 const& v)
{
    Vec2 result(multiplier * v.x, multiplier * v.y);
    return result;
}

} // namespace scmath
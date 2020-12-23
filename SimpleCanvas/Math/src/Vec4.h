#pragma once

#include <ostream>

namespace scmath
{
class Vec3;

class Vec4
{
public:
    Vec4(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f, float pW = 0.0f);
    Vec4(Vec3 const& vec3, float pW);
    Vec4(Vec4 const& other);
    Vec4(Vec4&& other);

    /**
     * Calculate dot product of vector and other vector
     * 
     * @param other second vector to calculate dot product
     * @return vector length in float
    */
    float dot(Vec4 const& other) const;

    /**
     * Calculate length(magnitude) of vector
     * 
     * @return vector length in float
    */
    float length() const;

    /**
     * Calculate vector with length=1.
     * Normalized vector can not be zero!
     * 
     * @return normalized vector with length=1
    */
    Vec4 normalized() const;

    /**
     * Checks if vector's all attributes are 0
     *
     * @return bool value that tells if vector's attributes are 0
    */
    bool isZero() const;

    /**
     * Calculates the distance between this vector and other vector
     * 
     * @param other Vec2, destination vector
     * @return float distance between this and other vector
    */
    float distance(Vec4 const& other) const;

    /**
     * Build a string based on x, y, z and w like:
     * Vec4(x, y, z, w)
     * 
     * @return Vec4 in string
    */
    std::string to_string() const;

    Vec4& operator=(Vec4&& other);
    Vec4& operator=(Vec4 const& other);
    Vec4 operator+(Vec4 const& other) const;
    Vec4 operator-(Vec4 const& other) const;
    Vec4 operator-() const;
    bool operator==(Vec4 const& other) const;
    bool operator!=(Vec4 const& other) const;
    Vec4 operator*(float multiplier) const;
    Vec4 operator/(float divider) const;
    float operator[](int i) const;
    float& operator[](int i);
    operator float *();

    static float dot(Vec4 const& v1, Vec4 const& v2);

    /**
     * Calculates the distance between first vector and second vector
     * 
     * @param first Vec4, begin vector
     * @param second Vec4, end vector
     * @return float distance between first and second vector
    */
    static Vec4 distance(Vec4 const& first, Vec4 const& second);

    friend std::ostream & operator<<(std::ostream &os, Vec4 const& v);
    friend std::ostream & operator<<(Vec4 const& v, std::ostream &os);
    friend Vec4 operator*(float multiplier, Vec4 const& v);

    union
    {
        struct { float x, y, z, w; };
        float arr[4];
    };
};
} // namespace scmath
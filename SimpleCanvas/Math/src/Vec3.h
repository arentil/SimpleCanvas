#pragma once

#include <ostream>

namespace scmath 
{
class Vec3
{
public:
    Vec3(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f);
    Vec3(Vec3 const& other);
    Vec3(Vec3&& other);

    /**
     * Calculate dot product of vector and other vector
     * 
     * @param other second vector to calculate dot product
     * @return vector length in float
    */
    float dot(Vec3 const& other) const;

    /**
     * Calculate cross product of vector and other vector
     * 
     * @param other second vector to caltulate cross product
     * @return cross product in vector
    */
    Vec3 cross(Vec3 const& other) const;

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
    Vec3 normalized() const;

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
    float distance(Vec3 const& other) const;

    /**
     * Reflects the x, y, z on a plane perpendicular to normal
     * 
     * @param normal Vec3, must be normalized and pointing up
     * @return Vec3 reflected vector to original
    */
    Vec3 reflect(Vec3 const& normal) const;

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal normalized vector pointing up
     * @return Vec3 refracted vector
    */
    Vec3 refract(Vec3 const& normal, float factor) const;

    /**
     * Build a string based on x, y, z and w like:
     * Vec3(x, y, z)
     * 
     * @return Vec3 in string
    */
    std::string Vec3::to_string() const;

    Vec3& operator=(Vec3&& other);
    Vec3& operator=(Vec3 const& other);
    Vec3 operator+(Vec3 const& other) const;
    Vec3 operator-(Vec3 const& other) const;
    bool operator==(Vec3 const& other) const;
    bool operator!=(Vec3 const& other) const;
    Vec3 operator*(float multiplier) const;
    Vec3 operator/(float divider) const;
    float operator[](int i) const;
    float& operator[](int i);
    operator float *();

    static float dot(Vec3 const& v1, Vec3 const& v2);
    static Vec3 cross(Vec3 const& v1, Vec3 const& v2);
    static Vec3 projection(Vec3 const& v, Vec3 const& onVector);
    static Vec3 perpendicular(Vec3 const& v, Vec3 const& onVector);

    /**
     * Reflects the in vector on a plane perpendicular to normal
     * 
     * @param in Vec3, input vector
     * @param normal Vec3, must be normalized and pointing up
     * @return Vec3 reflected vector to original
    */
    static Vec3 reflect(Vec3 const& in, Vec3 const& normal);

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal normalized vector pointing up
     * @return Vec3 refracted vector
    */
    static Vec3 refract(Vec3 const& in, Vec3 const& normal, float factor);

    /**
     * Calculates the distance between first vector and second vector
     * 
     * @param first Vec3, begin vector
     * @param second Vec3, end vector
     * @return float distance between first and second vector
    */
    static Vec3 distance(Vec3 const& first, Vec3 const& second);

    friend std::ostream & operator<<(std::ostream &os, Vec3 const& v);
    friend std::ostream & operator<<(Vec3 const& v, std::ostream &os);
    friend Vec3 operator*(float multiplier, Vec3 const& v);

    union 
    {
        struct { float x, y, z; };
        float arr[3];
    };
};
} // namespace scmath
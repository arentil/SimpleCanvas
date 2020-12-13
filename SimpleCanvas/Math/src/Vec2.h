#include <ostream>

namespace scmath 
{
class Vec2
{
public:
    Vec2(float pX = 0, float pY = 0);
    Vec2(Vec2 const& other);
    Vec2(Vec2&& other);

    /**
     * Calculate dot product of vector and other vector
     * 
     * @param other second vector to calculate dot product
     * @return vector length in float
    */
    float dot(Vec2 const& other) const;

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
    Vec2 normalized() const;

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
    float distance(Vec2 const& other) const;

    /**
     * Reflects the x, y on a plane perpendicular to normal
     * 
     * @param normal Vec2, must be normalized and pointing up
     * @return Vec2 reflected vector to original
    */
    Vec2 reflect(Vec2 const& normal) const;

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal normalized vector pointing up
     * @return Vec2 refracted vector
    */
    Vec2 refract(Vec2 const& normal, float factor) const;

    /**
     * Build a string based on x, y and w like:
     * Vec2(x, y)
     * 
     * @return Vec2 in string
    */
    std::string to_string() const;

    Vec2& operator=(Vec2&& other);
    Vec2& operator=(Vec2 const& other);
    Vec2 operator+(Vec2 const& other) const;
    Vec2 operator-(Vec2 const& other) const;
    bool operator==(Vec2 const& other) const;
    Vec2 operator*(float multiplier) const;
    Vec2 operator/(float divider) const;

    static float dot(Vec2 const& v1, Vec2 const& v2);
    static Vec2 projection(Vec2 const& v, Vec2 const& onVector);
    static Vec2 perpendicular(Vec2 const& v, Vec2 const& onVector);

        /**
     * Reflects the in vector on a plane perpendicular to normal
     * 
     * @param in Vec2, input vector
     * @param normal Vec2, must be normalized and pointing up
     * @return Vec2 reflected vector to original
    */
    static Vec2 reflect(Vec2 const& in, Vec2 const& normal);

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal normalized vector pointing up
     * @return Vec2 refracted vector
    */
    static Vec2 refract(Vec2 const& in, Vec2 const& normal, float factor);

    /**
     * Calculates the distance between first vector and second vector
     * 
     * @param first Vec2, begin vector
     * @param second Vec2, end vector
     * @return float distance between first and second vector
    */
    static Vec2 distance(Vec2 const& first, Vec2 const& second);

    friend std::ostream & operator<<(std::ostream &os, Vec2 const& v);
    friend std::ostream & operator<<(Vec2 const& v, std::ostream &os);
    friend Vec2 operator*(float multiplier, Vec2 const& v);

    float x, y;

};
} // namespace scmath
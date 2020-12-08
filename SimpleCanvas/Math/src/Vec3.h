#include <ostream>

namespace scmath 
{
class Vec3
{
public:
    Vec3(float pX = 0, float pY = 0, float pZ = 0);
    Vec3(Vec3 const& other);
    Vec3(Vec3&& other);

    float dot(Vec3 const& other) const;
    Vec3 cross(Vec3 const& other) const;

    /**
     * Calculate length(magnitude) of vector
     * 
     * @return vector length in float
    */
    float length() const;
    Vec3 normalized() const;
    bool isZero() const;

    /**
     * Reflects the x, y, z on a plane perpendicular to normal
     * 
     * @param normal - Vec3, must be normalized and pointing up
     * @return Vec3 reflected vector to original
    */
    Vec3 reflect(Vec3 const& normal) const;

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal - normalized vector pointing up
     * @return Vec3 refracted vector
    */
    Vec3 refract(Vec3 const& normal, float factor) const;

    Vec3& operator=(Vec3&& other);
    Vec3& operator=(Vec3 const& other);
    Vec3 operator+(Vec3 const& other) const;
    Vec3 operator-(Vec3 const& other) const;
    bool operator==(Vec3 const& other) const;
    Vec3 operator*(float multiplier) const;
    Vec3 operator/(float divider) const;

    static float dot(Vec3 const& v1, Vec3 const& v2);
    static Vec3 cross(Vec3 const& v1, Vec3 const& v2);
    static Vec3 projection(Vec3 const& v, Vec3 const& onVector);
    static Vec3 perpendicular(Vec3 const& v, Vec3 const& onVector);

    /**
     * Reflects the in vector on a plane perpendicular to normal
     * 
     * @param in - Vec3, input vector
     * @param normal - Vec3, must be normalized and pointing up
     * @return Vec3 reflected vector to original
    */
    static Vec3 reflect(Vec3 const& in, Vec3 const& normal);

    /**
     * Calculates vector refraction based on factor on plane perpendicular to normal
     * 
     * @param normal - normalized vector pointing up
     * @return Vec3 refracted vector
    */
    static Vec3 refract(Vec3 const& in, Vec3 const& normal, float factor);

    friend std::ostream & operator<<(std::ostream &os, scmath::Vec3 const& v);
    friend std::ostream & operator<<(scmath::Vec3 const& v, std::ostream &os);
    friend Vec3 operator*(float multiplier, Vec3 const& v);

    float x, y, z;
};
} // namespace scmath
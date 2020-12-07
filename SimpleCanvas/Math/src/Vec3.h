#include <ostream>

namespace scmath 
{
class Vec3
{
public:
    Vec3(float pX = 0, float pY = 0, float pZ = 0);
    Vec3(Vec3 const& other);

    // iloczyn skalarny
    float dot(Vec3 const& other) const;

    // iloczyn wektorowy
    Vec3 cross(Vec3 const& other) const;

    Vec3& operator=(Vec3 const& other);
    Vec3 operator+(Vec3 const& other) const;
    Vec3 operator-(Vec3 const& other) const;
    bool operator==(Vec3 const& other) const;
    Vec3 operator*(float multiplier) const;
    Vec3 operator*(int multiplier) const;
    Vec3 operator*(Vec3 const& other) const;
    Vec3 operator/(float divider) const;
    Vec3 operator/(int divider) const;

    // also called as magnitute
    float length() const;
    Vec3 normalized() const;
    bool isZero() const;

    static float dot(Vec3 const& v1, Vec3 const& v2);
    static Vec3 cross(Vec3 const& v1, Vec3 const& v2);
    static Vec3 projection(Vec3 const& v, Vec3 const& onVector);
    static Vec3 perpendicular(Vec3 const& v, Vec3 const& onVector);

    friend std::ostream & operator<<(std::ostream &os, scmath::Vec3 const& v);
    friend std::ostream & operator<<(scmath::Vec3 const& v, std::ostream &os);
    friend Vec3 operator*(float multiplier, Vec3 const& v);

    float x, y, z;
};
} // namespace scmath
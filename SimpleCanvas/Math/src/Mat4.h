#pragma once

#include <ostream>

#include "Vec4.h"

namespace scmath
{
class Vec3;
// column-major for sake of OpenGL effectivness
class Mat4
{
public:
    Mat4();
    Mat4(Vec4 const& v1, Vec4 const& v2, Vec4 const& v3, Vec4 const& v4);
    Mat4(Mat4 const& mat);
    Mat4(Mat4 && mat);

    std::string to_string() const;

    Mat4& operator=(Mat4 && other);
    Mat4& operator=(Mat4 const& other);
    bool operator==(Mat4 const& other) const;
    Mat4 operator+(Mat4 const& other) const;
    Mat4 operator-(Mat4 const& other) const;
    Mat4 operator-() const;
    Mat4 operator*(float multiplier) const;
    Mat4 operator/(float divider) const;
    Mat4 operator*(Mat4 const& other) const;
    Vec4 operator*(Vec4 const& v) const;
    Vec4& operator[](int i);
    Vec4 operator[](int i) const;
    operator float *();

    static Mat4 identity();
    static Mat4 translate(Vec3 const& v);
    static Mat4 translate(float x, float y, float z);
    static Mat4 rotateX(float angle);
    static Mat4 rotateY(float angle);
    static Mat4 rotateZ(float angle);
    static Mat4 rotate(float angleX, float angleY, float angleZ);

    //rotate by angle in radians around any axis given by x, y, z. Vector created from x, y, z must be normalized
    static Mat4 rotate(float angle, float axisX, float axisY, float axisZ);
    //rotate by angle in radians around any axis given by normalized Vec3
    static Mat4 rotate(float angle, Vec3 const& axis);

    static Mat4 scale(float sX, float sY, float sZ);
    static Mat4 scale(Vec3 const& v);

    // up is a normalized vector pointing up
    static Mat4 lookAt(Vec3 const& eye, Vec3 const& center, Vec3 const& up);

    static Mat4 frustum(float left, float right, float bottom, float top, float near, float far);
    static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);
    static Mat4 perspective(float fov, float aspect, float near, float far);

    friend std::ostream & operator<<(std::ostream &os, Mat4 const& m);
    friend std::ostream & operator<<(Mat4 const& m, std::ostream &os);

    Vec4 matrix[4];
};
} // namespace sc
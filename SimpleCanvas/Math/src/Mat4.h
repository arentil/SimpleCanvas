#pragma once

#include <iostream>

#include "Vec4.h"

namespace scmath
{
// column-major for sake of OpenGL effectivness
class Mat4
{
public:
    Mat4();
    Mat4(Vec4 const& v1, Vec4 const& v2, Vec4 const& v3, Vec4 const& v4);
    Mat4(Mat4 const& mat);
    Mat4(Mat4 && mat);

    Mat4& operator=(Mat4 && other);
    Mat4& operator=(Mat4 const& other);
    bool operator==(Mat4 const& other) const;
    Mat4 operator+(Mat4 const& other) const;
    Mat4 operator-(Mat4 const& other) const;
    Vec4& operator[](int i);
    Vec4 operator[](int i) const;
    operator float *();

    static Mat4 identity();

    Vec4 matrix[4];
};
} // namespace sc
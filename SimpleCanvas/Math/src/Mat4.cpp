#include "Mat4.h"

#include "Utility.h"

#include <cassert>

namespace scmath
{
Mat4::Mat4()
: matrix{Vec4(), Vec4(), Vec4(), Vec4()}
{}

Mat4::Mat4(Vec4 const& v1, Vec4 const& v2, Vec4 const& v3, Vec4 const& v4)
: matrix{v1, v2, v3, v4}
{}

Mat4::Mat4(Mat4 const& mat)
: matrix{mat[0], mat[1], mat[2], mat[3]}
{}

Mat4::Mat4(Mat4 && mat)
: matrix{mat[0], mat[1], mat[2], mat[3]}
{
    mat[0] = 0;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = 0;
}

Mat4& Mat4::operator=(Mat4 && other)
{
    matrix[0] = other[0];
    matrix[1] = other[1];
    matrix[2] = other[2];
    matrix[3] = other[3];
    other[0] = 0;
    other[1] = 0;
    other[2] = 0;
    other[3] = 0;
    return *this;
}

Mat4& Mat4::operator=(Mat4 const& other)
{
    matrix[0] = other[0];
    matrix[1] = other[1];
    matrix[2] = other[2];
    matrix[3] = other[3];
    return *this;
}

bool Mat4::operator==(Mat4 const& other) const
{
    for (int i = 0; i < 4; i++)
        if (matrix[i] != other[i])
            return false;
    return true;
}

Mat4 Mat4::operator+(Mat4 const& other) const
{
    return Mat4(
        matrix[0] + other[0],
        matrix[1] + other[1],
        matrix[2] + other[2],
        matrix[3] + other[3]
    );
}

Mat4 Mat4::operator-(Mat4 const& other) const
{
    return Mat4(
        matrix[0] - other[0],
        matrix[1] - other[1],
        matrix[2] - other[2],
        matrix[3] - other[3]
    );
}

Vec4& Mat4::operator[](int i)
{
    assert(i < 4 && i >= 0);
    return matrix[i];
}

Vec4 Mat4::operator[](int i) const
{
    assert(i < 4 && i >= 0);
    return matrix[i];
}

Mat4::operator float *()
{
    return (float *)matrix;
}

// ----- static methods -----
Mat4 Mat4::identity()
{
    Vec4 v1(1, 0, 0, 0);
    Vec4 v2(0, 1, 0, 0);
    Vec4 v3(0, 0, 1, 0);
    Vec4 v4(0, 0, 0, 1);
    return Mat4(v1, v2, v3, v4);
}
}
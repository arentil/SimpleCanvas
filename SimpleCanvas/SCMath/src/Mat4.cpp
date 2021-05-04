#include "Mat4.h"

#include <cassert>
#include <iostream>
#include <string>

#include "Utility.h"
#include "Vec3.h"

namespace scmath
{
Mat4::Mat4()
: Mat4(Mat4::identity())
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

std::string Mat4::to_string() const
{
    std::string result = "\n";
    for (int i = 0; i < 4; i++)
    {
        result += "|";
        for (int j = 0; j < 4; j++)
        {
            result += std::to_string(matrix[i][j]) + ",\t";
        }
        result.erase(result.size() - 2);
        result += "|\n";
    }
    result.pop_back();
    return result;
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

Mat4 Mat4::operator-() const
{
    return *this * (-1);
}

Mat4 Mat4::operator*(float multiplier) const
{
    return Mat4(
        matrix[0] * multiplier,
        matrix[1] * multiplier,
        matrix[2] * multiplier,
        matrix[3] * multiplier
    );
}

Mat4 Mat4::operator/(float divider) const
{
    return Mat4(
        matrix[0] / divider,
        matrix[1] / divider,
        matrix[2] / divider,
        matrix[3] / divider
    );
}
Mat4 Mat4::operator*(Mat4 const& other) const
{
    Mat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++)
                sum += matrix[k][i] * other[j][k];
            result[j][i] = sum;
        }
    }
    return result;
}

Vec4 Mat4::operator*(Vec4 const& v) const
{
    Vec4 result;
    for (int i = 0; i < 4; i++)
    {
        float sum = 0.0f;
        for (int j = 0; j < 4; j++)
            sum += matrix[j][i] * v[j];

        result[i] = sum;
    }
    return result;
}

Vec3 Mat4::operator*(Vec3 const& v) const
{
    Vec4 result = operator*({v, 1.0f});
    return Vec3(result.x, result.y, result.z);
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

Mat4::operator const float*() const
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

Mat4 Mat4::translate(Vec3 const& v)
{
    return Mat4(
        Vec4(1, 0, 0, 0),
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 0),
        Vec4(v, 1)
    );
}

Mat4 Mat4::translate(Vec4 const& v)
{
        return Mat4(
        Vec4(1, 0, 0, 0),
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 0),
        v
    );
}

Mat4 Mat4::translate(float x, float y, float z)
{
    return Mat4(
        Vec4(1, 0, 0, 0),
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 0),
        Vec4(x ,y, z, 1)
    );
}

Mat4 Mat4::translate(float x, float y, float z, float w)
{
    return Mat4(
        Vec4(1, 0, 0, 0),
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 0),
        Vec4(x ,y, z, w)
    );
}

Mat4 Mat4::rotateX(float theta)
{
    float const cosTheta = std::cos(theta);
    float const sinTheta = std::sin(theta);
    return Mat4(
        {1, 0, 0, 0},
        {0, cosTheta, -sinTheta, 0},
        {0, sinTheta, cosTheta, 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::rotateY(float theta)
{
    float const cosTheta = std::cos(theta);
    float const sinTheta = std::sin(theta);
    return Mat4(
        {cosTheta, 0, sinTheta, 0},
        {0, 1, 0, 0},
        {-sinTheta, 0, cosTheta, 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::rotateZ(float theta)
{
    float const cosTheta = std::cos(theta);
    float const sinTheta = std::sin(theta);
    return Mat4(
        {cosTheta, sinTheta, 0, 0},
        {-sinTheta, cosTheta, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::rotate(float angleX, float angleY, float angleZ)
{
    float const cosX = std::cos(angleX);
    float const sinX = std::sin(angleX);
    float const cosY = std::cos(angleY);
    float const sinY = std::sin(angleY);
    float const cosZ = std::cos(angleZ);
    float const sinZ = std::sin(angleZ);
    return Mat4(
        {cosY * cosZ, -cosY * sinZ, sinY, 0},
        {cosX * sinZ + sinX * sinY * cosZ, cosX * cosZ - sinX * sinY * sinZ, -sinX * cosY, 0},
        {sinX * sinZ - cosX * sinY * sinZ, sinX * cosZ + cosX * sinY * sinZ, cosX * sinY, 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::rotate(float angle, float axisX, float axisY, float axisZ)
{
    float const cosTheta = std::cos(angle);
    float const sinTheta = std::sin(angle);
    return Mat4(
        {cosTheta - cosTheta * (axisX * axisX), -cosTheta * axisX * axisY + sinTheta * axisZ, -cosTheta * axisX * axisZ - sinTheta * axisY, 0},
        {-cosTheta * axisX * axisY - sinTheta * axisZ, cosTheta - cosTheta * (axisY * axisY), -cosTheta * axisY * axisZ + sinTheta * axisX, 0},
        {-cosTheta * axisX * axisZ + sinTheta * axisY, -cosTheta * axisY * axisZ - sinTheta * axisX, cosTheta + (1 - cosTheta * (axisZ * axisZ)), 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::rotate(float angle, Vec3 const& axis)
{
    return Mat4::rotate(angle, axis.x, axis.y, axis.z);
}

Mat4 Mat4::scale(float sX, float sY, float sZ)
{
    return Mat4(
        {sX, 0, 0, 0},
        {0, sY, 0, 0},
        {0, 0, sZ, 0},
        {0, 0, 0, 1}
    );
}

Mat4 Mat4::scale(Vec3 const& v)
{
    return Mat4::scale(v.x, v.y, v.z);
}

Mat4 Mat4::transpose(Mat4 const& m)
{
    return Mat4(
        {m[0][0], m[1][0], m[2][0], m[3][0]},
        {m[0][1], m[1][1], m[2][1], m[3][1]},
        {m[0][2], m[1][2], m[2][2], m[3][2]},
        {m[0][3], m[1][3], m[2][3], m[3][3]}
    );
}

float Mat4::det(Mat4 const& m)
{
    float a11 = m[0][0], a12 = m[1][0], a13 = m[2][0], a14 = m[3][0];
    float a21 = m[0][1], a22 = m[1][1], a23 = m[2][1], a24 = m[3][1];
    float a31 = m[0][2], a32 = m[1][2], a33 = m[2][2], a34 = m[3][2];
    float a41 = m[0][3], a42 = m[1][3], a43 = m[2][3], a44 = m[3][3];

    return (a11 * a22 * a33 * a44) + (a11 * a23 * a34 * a42) + (a11 * a24 * a32 * a43) -
           (a11 * a24 * a33 * a42) - (a11 * a23 * a32 * a44) - (a11 * a22 * a34 * a43) -
           (a12 * a21 * a33 * a44) - (a13 * a21 * a34 * a42) - (a14 * a21 * a32 * a43) +
           (a14 * a21 * a33 * a42) + (a13 * a21 * a32 * a44) + (a12 * a21 * a34 * a43) +
           (a12 * a23 * a31 * a44) + (a13 * a24 * a31 * a42) + (a14 * a22 * a31 * a43) -
           (a14 * a23 * a31 * a42) - (a13 * a22 * a31 * a44) - (a12 * a24 * a31 * a43) -
           (a12 * a23 * a34 * a41) - (a13 * a24 * a32 * a41) - (a14 * a22 * a33 * a41) +
           (a14 * a23 * a32 * a41) + (a13 * a22 * a34 * a41) + (a12 * a24 * a33 * a41);
}

Mat4 Mat4::adjugate(Mat4 const& m)
{
    float a11 = m[0][0], a12 = m[1][0], a13 = m[2][0], a14 = m[3][0];
    float a21 = m[0][1], a22 = m[1][1], a23 = m[2][1], a24 = m[3][1];
    float a31 = m[0][2], a32 = m[1][2], a33 = m[2][2], a34 = m[3][2];
    float a41 = m[0][3], a42 = m[1][3], a43 = m[2][3], a44 = m[3][3];

    Vec4 col1((a22 * a33 * a44) + (a23 * a34 * a42) + (a24 * a32 * a43) - (a24 * a33 * a42) - (a23 * a32 * a44) - (a22 * a34 * a43),
              -(a21 * a33 * a44) - (a23 * a34 * a41) - (a24 * a31 * a43) + (a24 * a33 * a41) + (a23 * a31 * a44) + (a21 * a34 * a43),
               (a21 * a32 * a44) + (a22 * a34 * a41) + (a24 * a31 * a42) - (a24 * a32 * a41) - (a22 * a31 * a44) - (a21 * a34 * a42),
              -(a21 * a32 * a43) - (a22 * a33 * a41) - (a23 * a31 * a42) + (a23 * a32 * a41) + (a22 * a31 * a43) + (a21 * a33 * a42));

    Vec4 col2(-(a12 * a33 * a44) - (a13 * a34 * a42) - (a14 * a32 * a43) + (a14 * a33 * a42) + (a13 * a32 * a44) + (a13 * a43 * a43),
               (a11 * a33 * a44) + (a13 * a34 * a41) + (a14 * a31 * a43) - (a14 * a33 * a41) - (a13 * a31 * a44) - (a11 * a34 * a43),
               -(a11 * a23 * a44) - (a13 * a24 * a41) - (a14 * a21 * a42) + (a14 * a23 * a41) + (a13 * a21 * a44) + (a11 * a24 * a43),
               (a11 * a32 * a43) + (a12 * a33 * a41) + (a13 * a31 * a42) - (a13 * a32 * a41) - (a12 * a31 * a43) - (a11 * a33 * a42));

    Vec4 col3( (a12 * a23 * a44) + (a13 * a24 * a42) + (a14 * a22 * a43) - (a14 * a23 * a42) - (a13 * a22 * a44) - (a12 * a24 * a43),
              -(a11 * a23 * a44) - (a13 * a24 * a41) - (a14 * a21 * a43) + (a14 * a23 * a41) + (a13 * a21 * a44) + (a11 * a24 * a43),
               (a11 * a22 * a44) + (a12 * a24 * a41) + (a41 * a21 * a42) - (a14 * a22 * a41) - (a12 * a21 * a44) - (a11 * a24 * a42),
              -(a11 * a22 * a43) - (a12 * a23 * a41) - (a13 * a21 * a42) + (a12 * a22 * a41) + (a12 * a21 * a43) + (a11 * a23 * a42));

    Vec4 col4(-(a21 * a23 * a34) - (a12 * a24 * a32) - (a14 * a22 * a33) + (a14 * a23 * a32) + (a13 * a22 * a34) + (a12 * a24 * a33),
               (a11 * a23 * a34) + (a13 * a24 * a31) + (a14 * a21 * a33) - (a14 * a23 * a31) - (a13 * a21 * a34) - (a11 * a24 * a33),
              -(a11 * a22 * a34) - (a12 * a24 * a31) - (a14 * a21 * a32) + (a14 * a22 * a31) + (a12 * a21 * a34) + (a11 * a24 * a32),
               (a11 * a22 * a33) + (a12 * a23 * a31) + (a13 * a21 * a32) - (a13 * a22 * a31) - (a12 * a21 * a33) - (a11 * a23 * a32));

    Mat4 result(col1, col2, col3, col4);
    return result;
}

Mat4 Mat4::inverse(Mat4 const& m)
{
    if (float det = Mat4::det(m); !f_equal(det, 0.0f))
        return Mat4::adjugate(m) / det;
    return Mat4::identity();
}

Mat4 Mat4::lookAt(Vec3 const& eye, Vec3 const& target, Vec3 const& up)
{
	Vec3 zaxis = (eye - target).normalized();
	Vec3 xaxis = Vec3::cross(up, zaxis).normalized();
	Vec3 yaxis = zaxis.cross(xaxis);

	return Mat4(
	{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
	{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
	{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
	{ -Vec3::dot(xaxis, eye), -Vec3::dot(yaxis, eye), -Vec3::dot(zaxis, eye), 1.0f }
	);
}

Mat4 Mat4::frustum(float left, float right, float bottom, float top, float near, float far)
{
    return Mat4(
        {2 * near / (right - left), 0, 0, 0},
        {0, 2 * near / (top - bottom), 0, 0},
        {(right + left) / (right - left), (top + bottom) / (top - bottom), (near + far) / (near - far), -1},
        {0, 0, 2 * near * far / (near - far), 0}
    );
}

Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    return Mat4(
        {2 / (right - left), 0, 0, 0},
        {0, 2 / (top - bottom), 0, 0},
        {0, 0, 2 / (near - far), 0},
        {(left + right) / (left - right), (top + bottom) / (top - bottom), (near + far) / (near - far), 1}
    );
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
    float q = 1 / std::tan(degToRad(fov / 2));
    float A = q / aspect;
    float B = (near + far) / (near - far);
    float C = 2 * near * far / (near - far);
    return Mat4(
        {A, 0, 0, 0},
        {0, q, 0, 0},
        {0, 0, B, -1},
        {0, 0, C, 0}
    );
}

// ----- friends -----
std::ostream & operator<<(std::ostream &os, scmath::Mat4 const& m)
{
    os << m.to_string();
    return os;
}

std::ostream & operator<<(scmath::Mat4 const& m, std::ostream &os)
{
    os << m;
    return os;
}
} // namespace scmath
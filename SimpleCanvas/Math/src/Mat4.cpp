#include "Mat4.h"

#include <cassert>
#include <string>
#include <cmath>

#include "Utility.h"

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

std::string Mat4::to_string() const
{
    std::string result = "";
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
            sum += matrix[i][j] * v[j];

        result[i] = sum;
    }
    return result;
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

Mat4 Mat4::translate(Vec3 const& v)
{
    return Mat4(
        Vec4(1, 0, 0, 0),
        Vec4(0, 1, 0, 0),
        Vec4(0, 0, 1, 0),
        Vec4(v, 1)
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
        {-cosTheta * axisX * axisZ + sinTheta * axisY, -cosTheta * axisY * axisZ - sinTheta * axisX, cosTheta - cosTheta * (axisZ * axisZ), 0},
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

Mat4 Mat4::lookAt(Vec3 const& eye, Vec3 const& center, Vec3 const& up)
{
    Vec3 f = Vec3::normalized(center - eye);   // looking forward vector
    Vec3 s = Vec3::cross(f, up);            // side looking vector
    Vec3 u = Vec3::cross(s, f);             // camera upper
    return Mat4(
        {f, 0},
        {u, 0},
        {f, 0},
        {-eye, 1}
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

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
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
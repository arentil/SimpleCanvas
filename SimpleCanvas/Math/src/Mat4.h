#pragma once

#include <iostream>

#include <array>

#include "Vec4.h"

namespace scmath
{
// column-major for sake of OpenGL effectivness
class Mat4
{
public:
    Mat4();
    Mat4(Vec4 const& v1, Vec4 const& v2, Vec4 const& v3, Vec4 const& v4);

    static Mat4 identity();

    std::array<Vec4, 4> matrix;
};
} // namespace sc
#pragma once

#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

namespace scmath
{
constexpr float PI = (float)M_PI;
constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
constexpr float FLOAT_MIN = std::numeric_limits<float>::min();

inline bool f_equal(float first, float second)
{
    return std::fabs(first - second) < std::numeric_limits<float>::epsilon();
}

inline float radToDeg(float rad)
{
    return rad * 180 / PI;
}

inline float degToRad(float deg)
{
    return deg * PI / 180;
}

template<typename T>
inline T square(T value)
{
    return value * value;
}
} // namespace scmath
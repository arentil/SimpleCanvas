#pragma once

#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

namespace scmath
{
inline bool f_equal(float first, float second)
{
    return std::fabs(first - second) < std::numeric_limits<float>::epsilon();
}

inline float radToDeg(float rad)
{
    return rad * 180 / M_PI;
}

inline float degToRad(float deg)
{
    return deg * M_PI / 180;
}

template<typename T>
inline T square(T value)
{
    return value * value;
}
} // namespace scmath
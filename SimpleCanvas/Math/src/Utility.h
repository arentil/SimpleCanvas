#pragma once

namespace scmath
{
bool f_equal(float first, float second);

float radToDeg(float rad);

float degToRad(float deg);

template<typename T>
inline T square(T value)
{
    return value * value;
}
} // namespace scmath
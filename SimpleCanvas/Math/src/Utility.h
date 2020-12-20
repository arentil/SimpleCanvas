#pragma once

#include <limits>
#include <cmath>

namespace scmath
{
bool f_equal(float first, float second);

template<typename T>
T square(T value)
{
    return value * value;
}
} // namespace scmath
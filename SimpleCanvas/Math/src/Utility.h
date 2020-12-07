#include <limits>
#include <cmath>

namespace scmath
{
bool equal(float first, float second)
{
    return std::fabs(first - second) < std::numeric_limits<float>::epsilon();
}

template<typename T>
T square(T value)
{
    return value * value;
}
}
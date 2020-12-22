#include "Utility.h"

#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

namespace scmath
{
bool f_equal(float first, float second)
{
    return std::fabs(first - second) < std::numeric_limits<float>::epsilon();
}

float radToDeg(float rad)
{
    return rad * 180 / M_PI;
}

float degToRad(float deg)
{
    return deg * M_PI / 180;
}
} // namespace scmath
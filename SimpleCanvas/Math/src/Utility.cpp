#include "Utility.h"

namespace scmath
{
bool equal(float first, float second)
{
    return std::fabs(first - second) < std::numeric_limits<float>::epsilon();
}
} // namespace scmath
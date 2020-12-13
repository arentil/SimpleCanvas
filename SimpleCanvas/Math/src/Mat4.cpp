#include "Mat4.h"

namespace scmath
{
Mat4::Mat4()
 : matrix({{Vec4(), Vec4(), Vec4(), Vec4()}})
{

}

Mat4::Mat4(Vec4 const& v1, Vec4 const& v2, Vec4 const& v3, Vec4 const& v4)
: matrix({{v1, v2, v3, v4}})
{}
// ----- static methods -----
Mat4 Mat4::identity()
{
    Vec4 v1(1, 0, 0, 0);
    Vec4 v2(0, 1, 0, 0);
    Vec4 v3(0, 0, 1, 0);
    Vec4 v4(0, 0, 0, 1);
    return Mat4(v1, v2, v3, v4);
}
}
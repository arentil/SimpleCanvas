#include "gtest/gtest.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "Mat4.h"
#include "Utility.h"

using namespace scmath;

bool arr_equal(float *first, float *second, int size)
{
    for (int i = 0; i < size; i++)
        if (!f_equal(first[i], first[i]))
            return false;
    return true;
}

Mat4 buildByRows(std::vector<float> const& r1,
                 std::vector<float> const& r2,
                 std::vector<float> const& r3,
                 std::vector<float> const& r4)
{
    return Mat4(
        {r1[0], r2[0], r3[0], r4[0]},
        {r1[1], r2[1], r3[1], r4[1]},
        {r1[2], r2[2], r3[2], r4[2]},
        {r1[3], r2[3], r3[3], r4[3]}
    );
}

class Mat4Test : public ::testing::Test
{
};

TEST_F(Mat4Test, MAT4_ASSERT_TEST)
{
    ASSERT_DEATH(Mat4()[5], "i < 4 && i >= 0");
    ASSERT_DEATH(Mat4()[-1], "i < 4 && i >= 0");
}

TEST_F(Mat4Test, MAT4_ADD_TEST)
{
    Mat4 first = buildByRows(
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    );

    Mat4 second = buildByRows(
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    );

    Mat4 expect = buildByRows(
        {17, 17, 17, 17},
        {17, 17, 17, 17},
        {17, 17, 17, 17},
        {17, 17, 17, 17}
    );

    EXPECT_EQ(expect, first + second);
}

TEST_F(Mat4Test, MAT4_SUB_TEST)
{
    Mat4 first = buildByRows(
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    );

    Mat4 second = buildByRows(
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    );

    Mat4 expect = buildByRows(
        {15, 13, 11, 9},
        {7, 5, 3, 1},
        {-1, -3, -5, -7},
        {-9, -11, -13, -15}
    );

    EXPECT_EQ(expect, first - second);
}

TEST_F(Mat4Test, MAT4_IMPLICIT_FLOAT_ARRAY_CONVERSION_TEST)
{
    Vec4 v1(1, 2, 3, 4);
    Vec4 v2(5, 6, 7, 8);
    Vec4 v3(9, 10, 11, 12);
    Vec4 v4(13, 14, 15, 16);
    Mat4 result(v1, v2, v3, v4);
    float *resultArray = result;

    float expected[] = 
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    EXPECT_TRUE(arr_equal(expected, resultArray, 16));
}

TEST_F(Mat4Test, MAT4_MULTIPLY_TEST)
{
    Mat4 mat1 = buildByRows(
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4}
    );

    Mat4 mat2 = buildByRows(
        {4, 4, 4, 4},
        {3, 3, 3, 3},
        {2, 2, 2, 2},
        {1, 1, 1, 1}
    );

    Mat4 expected = buildByRows(
        {10, 10, 10, 10},
        {20, 20, 20, 20},
        {30, 30, 30, 30},
        {40, 40, 40, 40}
    );

    EXPECT_EQ(expected, mat1 * mat2);
}

TEST_F(Mat4Test, MAT4_MULTIPLY_IDENTITY_MATRIX_TEST)
{
    Vec4 v(1, 2, 3, 4);

    EXPECT_EQ(v, Mat4::identity() * v);
}
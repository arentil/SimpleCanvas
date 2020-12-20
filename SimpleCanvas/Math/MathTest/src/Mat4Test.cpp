#include "gtest/gtest.h"

#include <iostream>
#include <algorithm>
#include <iterator>

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
    Mat4 first(
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    );

    Vec4 v5(16, 15, 14, 13);
    Vec4 v6(12, 11, 10, 9);
    Vec4 v7(8, 7, 6, 5);
    Vec4 v8(4, 3, 2, 1);
    Mat4 second(v5, v6, v7, v8);

    Mat4 expect(
        {17, 17, 17, 17},
        {17, 17, 17, 17},
        {17, 17, 17, 17},
        {17, 17, 17, 17}
    );

    EXPECT_EQ(expect, first + second);
}

TEST_F(Mat4Test, MAT4_SUB_TEST)
{
    Vec4 v1(16, 15, 14, 13);
    Vec4 v2(12, 11, 10, 9);
    Vec4 v3(8, 7, 6, 5);
    Vec4 v4(4, 3, 2, 1);
    Mat4 first(v1, v2, v3, v4);

    Mat4 second(
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    );

    Mat4 expect(
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
#include "gtest/gtest.h"

#include <iostream>

#include "Vec3.h"

using namespace scmath;

class Vec3Test : public ::testing::Test
{
};

TEST_F(Vec3Test, VEC3_DOT_PRODUCT_TEST)
{   
    Vec3 v1(1, 1, 1);
    Vec3 v2(1, 1, 1);
    float expected = 3.f;

    EXPECT_EQ(expected, v1.dot(v2));

    v1 = {1, 2, 3};
    v2 = {4, 5, 6};
    expected = 32.f;

    EXPECT_EQ(expected, v1.dot(v2));
}

TEST_F(Vec3Test, VEC3_CROSS_PRODUCT_TEST)
{   
    Vec3 v1(1, 1, 1);
    Vec3 v2(1, 1, 1);
    Vec3 expected(0, 0, 0);

    EXPECT_EQ(expected, v1.cross(v2));
    
    expected = {-3, 6, -3};
    v1 = {1, 2, 3};
    v2 = {4, 5, 6};
    EXPECT_EQ(expected, v1.cross(v2));
}

TEST_F(Vec3Test, VEC3_ADD_SUB_MULTIPLY_DIVIDE_TEST)
{
    Vec3 v1(5, 6, 7);
    Vec3 v2(1, 1, 1);
    Vec3 expected(6, 7 ,8);

    EXPECT_EQ(expected, v1 + v2);

    expected = {4, 5, 6};
    EXPECT_EQ(expected, v1 - v2);

    expected = {25, 30, 35};
    EXPECT_EQ(expected, v1 * 5.f);

    expected = {0.5f, 0.6f, 0.7f};
    EXPECT_EQ(expected, v1 / 10.f);
}

TEST_F(Vec3Test, VEC3_LENGTH_TEST)
{
    Vec3 v(2, 4, 4);
    float expected = 6.f;
    EXPECT_EQ(expected, v.length());
}

TEST_F(Vec3Test, VEC3_PROJECTION_TEST)
{
    Vec3 v1(1, 4, 0);
    Vec3 v2(4, 2, 4);
    Vec3 expected(4.f/3, 2.f/3, 4.f/3);

    EXPECT_EQ(expected, Vec3::projection(v1, v2));
}
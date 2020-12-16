#include "gtest/gtest.h"

#include <iostream>

#include "Vec3.h"

using namespace scmath;

class Vec3Test : public ::testing::Test
{
};

TEST_F(Vec3Test, VEC3_ASSERT_TEST)
{
    ASSERT_DEATH(Vec3() / 0.0f, "divider != 0.0f");
    ASSERT_DEATH(Vec3().normalized(), "!isZero");
    ASSERT_DEATH(Vec3()[-1], "i < 3 && i >= 0");
    ASSERT_DEATH(Vec3()[4], "i < 3 && i >= 0");
}

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
    ASSERT_DEATH(Vec3::projection(Vec3(), Vec3()), ".*!onNormal.isZero\\(\\).*");
}

TEST_F(Vec3Test, VEC3_REFLECT_TEST)
{
    Vec3 in(4, -4, 0);
    Vec3 normal(0, 1, 0);
    Vec3 expected(4, 4, 0);

    EXPECT_EQ(expected, Vec3::reflect(in, normal));
}

TEST_F(Vec3Test, VEC3_REFRACT_TEST)
{
    Vec3 in(4, -4, 0);
    Vec3 normal(0, 1, 0);

    // 1.0f factor means refract through air,
    // direction of result vector should be the same as input vector
    EXPECT_EQ(in.normalized(), Vec3::refract(in, normal, 1.0f));
}

TEST_F(Vec3Test, VEC3_IMPLICIT_FLOAT_ARRAY_CONVERSION_TEST)
{
    Vec3 arr(99, 55, 11);
    auto getArrItem = [](float *array, int i) -> float
    {
        return array[i];
    };
    EXPECT_EQ(99, getArrItem(arr, 0));
    EXPECT_EQ(55, getArrItem(arr, 1));
    EXPECT_EQ(11, getArrItem(arr, 2));
}
#include "math/Vector3.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

namespace pdEngineTest 
{

using Vector3 = pdEngine::Vector3;

class Vector3_test : public ::testing::Test 
    {
    protected:
        //virtual void SetUp();
        //virtual void TearDown();
    };


TEST_F(Vector3_test, ConstrucorsAndGetters)
{
    Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    Vector3 vec1 { 1.0f, 1.0f, 1.0f };
    ASSERT_EQ(vec0.getX(), 0.0f);
    ASSERT_EQ(vec0.getY(), 0.0f);
    ASSERT_EQ(vec0.getZ(), 0.0f);
    ASSERT_EQ(vec1.getX(), 1.0f);
    ASSERT_EQ(vec1.getY(), 1.0f);
    ASSERT_EQ(vec1.getZ(), 1.0f);
}

TEST_F(Vector3_test, DefaultConstructor)
{
	Vector3 def {};
    ASSERT_EQ(def.getX(), 0.0f);
    ASSERT_EQ(def.getY(), 0.0f);
    ASSERT_EQ(def.getZ(), 0.0f);
}

TEST_F(Vector3_test, Equality)
{
    Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    Vector3 vec00 { 0.0f, 0.0f, 0.0f };
    Vector3 vec1 { 1.0f, 1.0f, 1.0f };
    Vector3 vec11 { 1.0f, 1.0f, 1.0f };

	ASSERT_TRUE(vec0 == vec00);
	ASSERT_TRUE(vec1 == vec11);
	ASSERT_TRUE(vec1 != vec0);
	ASSERT_FALSE(vec0 == Vector3(1.0f, 0.1f, 0.1f));
}

TEST_F(Vector3_test, Length)
{
    Vector3 vec000 { 0.0f, 0.0f, 0.0f };
    Vector3 vec111 { 1.0f, 1.0f, 1.0f };
    Vector3 vec110 { 1.0f, 1.0f, 0.0f };
    Vector3 vec101 { 1.0f, 0.0f, 1.0f };
    Vector3 vec011 { 0.0f, 1.0f, 1.0f };

	ASSERT_FLOAT_EQ(0.0f, vec000.length());
	ASSERT_FLOAT_EQ(std::sqrt(3.0f), vec111.length());
	ASSERT_FLOAT_EQ(std::sqrt(2.0f), vec110.length());
    ASSERT_FLOAT_EQ(std::sqrt(2.0f), vec101.length());
    ASSERT_FLOAT_EQ(std::sqrt(2.0f), vec011.length());
}

TEST_F(Vector3_test, NormalizeZeroLengthVector)
{
    Vector3 vec000 { 0.0f, 0.0f, 0.0f };

    ASSERT_TRUE(vec000 == vec000.getNormalized());
    auto o = vec000.getNormalized();
    ASSERT_FLOAT_EQ(o.length(), 0.0f);

    ASSERT_TRUE(o == vec000);
    vec000.normalize();
    o.normalize();
    ASSERT_TRUE(o == vec000);
    ASSERT_FLOAT_EQ(o.length(), 0.0f);
}

TEST_F(Vector3_test, NormalizeOneOneOneVector)
{
    Vector3 v{ 1.0f, 1.0f, 1.0f };
    auto l = v.length();

    ASSERT_FLOAT_EQ(v.length(), l);

    v.normalize();

    ASSERT_FLOAT_EQ(1.0f, v.length());
    ASSERT_FLOAT_EQ(v.getX(), v.getY());
    ASSERT_FLOAT_EQ(v.getX(), v.getZ());
    ASSERT_FLOAT_EQ(v.getX() * l, 1.0f);
}

TEST_F(Vector3_test, GetNormalizedFromOneOneOneVector)
{
    Vector3 v { 1.0f, 1.0f, 1.0f };

    auto l = v.length();
    auto n = v.getNormalized();

    ASSERT_FLOAT_EQ(n.length(), 1.0f);

    ASSERT_FLOAT_EQ(n.getX(), n.getY());
    ASSERT_FLOAT_EQ(n.getX(), n.getZ());
    ASSERT_FLOAT_EQ(n.getX() * l, 1.0f);
}

TEST_F(Vector3_test, NormalizeVector)
{
    float x = 1213487.0f;
    float y = 0.000000986f;
    float z = 12336.9024f;
    Vector3 v { x, y, z };
    auto l = v.length();
    auto n = v.getNormalized();

    ASSERT_FALSE(n == v);
    ASSERT_FLOAT_EQ(n.length(), 1.0f);

    v.normalize();

    ASSERT_FLOAT_EQ(v.length(), 1.0f);

    ASSERT_FLOAT_EQ(v.getX() * l, x);
    ASSERT_FLOAT_EQ(v.getY() * l, y);
    ASSERT_FLOAT_EQ(v.getZ() * l, z);

    ASSERT_FLOAT_EQ(n.getX(), v.getX());
    ASSERT_FLOAT_EQ(n.getY(), v.getY());
    ASSERT_FLOAT_EQ(n.getZ(), v.getZ());
}


TEST_F(Vector3_test, DotProducts)
{
    Vector3 a { 2.0f, 3.0f, 4.0f };
    Vector3 b { 5.0f, 6.0f, 7.0f };

    auto res = 56.0f;
    ASSERT_FLOAT_EQ(dot(a,b), res);
}

TEST_F(Vector3_test, OperatorStarEquals)
{
    Vector3 a { 2.0f, 3.0f, 4.0f };
    a *= 2;
    ASSERT_FLOAT_EQ(a.getX(), 4.0f);
    ASSERT_FLOAT_EQ(a.getY(), 6.0f);
    ASSERT_FLOAT_EQ(a.getZ(), 8.0f);
}

TEST_F(Vector3_test, ScalarProduct)
{
    Vector3 a { 2.0f, 3.0f, 4.0f };
    a *= 2;
    ASSERT_FLOAT_EQ(a.getX(), 4.0f);
    ASSERT_FLOAT_EQ(a.getY(), 6.0f);
    ASSERT_FLOAT_EQ(a.getZ(), 8.0f);

    Vector3 b = (a*123);
    a = b*(1.0f/246.0f);
    ASSERT_FLOAT_EQ(a.getX(), 2.0f);
    ASSERT_FLOAT_EQ(a.getY(), 3.0f);
    ASSERT_FLOAT_EQ(a.getZ(), 4.0f);
}

}

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

	ASSERT_EQ(0, vec000.length());
	ASSERT_EQ(std::sqrt(3.0f), vec111.length());
	ASSERT_EQ(std::sqrt(2.0f), vec110.length());
	ASSERT_EQ(std::sqrt(2.0f), vec101.length());
	ASSERT_EQ(std::sqrt(2.0f), vec011.length());
}

}
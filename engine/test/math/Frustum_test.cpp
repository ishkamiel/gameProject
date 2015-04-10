#include "math/Frustum.h"
#include "math/Vector3.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace pdEngineTest 
{

const float PI = 3.141593f;

using namespace pdEngine;
//using Frustum = pdEngine::Frustum;

using ::testing::FloatEq;

class Frustum_test : public ::testing::Test 
    {

    protected:
        Frustum_test() {};
        virtual ~Frustum_test() {};

        virtual void SetUp() {};
        virtual void TearDown() {};
    };


TEST_F(Frustum_test, IsInsideEasyFrustum)
{
    Frustum f { 3, 1, 0.0f, 100.0f };
    PD_debug("Frustum is: {}", f);

    ASSERT_TRUE(f.isInside(Vector3(0,0,10)));

    ASSERT_FALSE(f.isInside(Vector3(0,0,-10)));
    ASSERT_FALSE(f.isInside(Vector3(10,0,0)));
    ASSERT_FALSE(f.isInside(Vector3(-10,0,0)));
    ASSERT_FALSE(f.isInside(Vector3(0,10,0)));
    ASSERT_FALSE(f.isInside(Vector3(0,-10,0)));
}

TEST_F(Frustum_test, DefaultFrustum)
{
    Frustum f {};
    ASSERT_TRUE(f.isInside(Vector3(0,0,10)));
    ASSERT_FALSE(f.isInside(Vector3(0,0,-10)));
}

TEST_F(Frustum_test, ISInsiderustumWithNegativeZ)
{
    Frustum f { PI/2.0f, 1, -10.0f, -100.0f };

    PD_debug("Frustum is: {}", f);

    ASSERT_TRUE(f.isInside(Vector3(0,0,-11)));
    ASSERT_TRUE(f.isInside(Vector3(1,1,-20)));
    ASSERT_TRUE(f.isInside(Vector3(-5,-5,-50)));

    ASSERT_FALSE(f.isInside(Vector3(0,0,-9)));
    ASSERT_FALSE(f.isInside(Vector3(0,0,-101)));
    ASSERT_FALSE(f.isInside(Vector3(-50,-50,-20)));
}

TEST_F(Frustum_test, IsInsideWithRadius)
{
	auto fov = PI/2.0f;
    Frustum f { fov, 1, -10.0f, -100.0f };

    ASSERT_TRUE(f.isInside(Vector3(0,0,-11), 1.0f));
    ASSERT_FALSE(f.isInside(Vector3(0,0,1000), 1.0f));

    ASSERT_TRUE(f.isInside(Vector3(0,0,0), 100.0f));
    ASSERT_FALSE(f.isInside(Vector3(0,0,0), 9.01f));

    ASSERT_TRUE(f.isInside(Vector3(0,0,-101), 1.1f));
    ASSERT_FALSE(f.isInside(Vector3(0,0,-101), 0.99f));

    ASSERT_TRUE(f.isInside(Vector3(0,100*tan(fov/2.0f)+0.5f,-100), 1.0f));
    ASSERT_FALSE(f.isInside(Vector3(0,100*tan(fov/2.0f+0.5f),-100), 0.1f));
}


}

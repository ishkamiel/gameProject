#include "math/Plane.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace pdEngineTest 
{

using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Plane = pdEngine::Plane;

class Plane_test : public ::testing::Test 
    {

    protected:
        Plane_test() {};
        virtual ~Plane_test() {};

        virtual void SetUp() {};
        virtual void TearDown() {};
    };


TEST_F(Plane_test, ConstrucorsAndEquality)
{
    Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    Vector3 vec11 { 1.0f, 0.0f, 0.0f };
    Plane coords { 1.0f, 0.0f, 0.0f, 0.0f };
    Plane vecs { vec0, vec11 };
    ASSERT_TRUE(coords == vecs);
    ASSERT_FLOAT_EQ(vecs.getNormal().length(), 1.0f);
    ASSERT_FLOAT_EQ(coords.getNormal().length(), 1.0f);
}

TEST_F(Plane_test, DistanceToPointOnPlane)
{
    Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    Vector3 vec1 { 1.0f, 0.0f, 0.0f };
    Plane p {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 1.0f, 0.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 0.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 1.0f, 0.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 1.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 1.0f, 2.0f }), 0.0f);
}

TEST_F(Plane_test, DistanceToPointWithOrigoPlane)
{
    Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    Vector3 vec1 { 1.0f, 0.0f, 0.0f };
    Plane p { vec0, vec1 };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.0f, 0.0f, 0.0f }), 1.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 5.0f, 1.0f, 0.0f }), 5.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.0f, 0.0f, 1.0f }), 1.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.1234f, 1.0f, 2.0f }), 1.1234f);
}

TEST_F(Plane_test, DistanceToPoint)
{
    Vector3 vec0 { 1.0f, 1.0f, 1.0f };
    Vector3 vec1 { 1.0f, 1.0f, 1.0f };
    Plane p { vec0, vec1 };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 0.0f }), std::sqrt(3.0f));
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.0f, 1.0f, 1.0f }), 0.0f);
    //ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.0f, 0.0f, 1.0f }), 1.0f);
    //ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.1234f, 1.0f, 2.0f }), 1.1234f);
}

}

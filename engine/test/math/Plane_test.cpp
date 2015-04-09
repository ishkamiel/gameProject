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

TEST_F(Plane_test, NormalNormalization)
{
}

TEST_F(Plane_test, NormalAndDistanceValues2d)
{
    Plane p {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 1.0f, 0.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), 0.0f);
    ASSERT_EQ(p.getNormal(), Vector3(1.0f, 0.0f, 0.0f));

    p = Plane {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 0.0f, 1.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), 0.0f);
    ASSERT_EQ(p.getNormal(), Vector3(0.0f, 1.0f, 0.0f));

    p = Plane {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 1.0f, 1.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), 0.0f);
    ASSERT_EQ(p.getNormal(), Vector3(std::sqrt(0.5f), std::sqrt(0.5f), 0.0f));

    p = Plane {
        Vector3 { 1.0f, 1.0f, 0.0f },
        Vector3 { 100.0f, 100.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), std::sqrt(2.0f));
    ASSERT_FLOAT_EQ(p.getNormal().length(), 1.0f);
    ASSERT_TRUE(p.isValid());

    ASSERT_NEAR(std::sqrt(0.5f), p.getNormal().getX(), 0.0001f);
    ASSERT_NEAR(std::sqrt(0.5f), p.getNormal().getY(), 0.0001f);

    p = Plane {
        Vector3 { 10.0f, 10.0f, 0.0f },
        Vector3 { 100.0f, 100.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), std::sqrt(200.0f));
    ASSERT_FLOAT_EQ(p.getNormal().length(), 1.0f);
    ASSERT_TRUE(p.isValid());

    ASSERT_NEAR(std::sqrt(0.5f), p.getNormal().getX(), 0.0001f);
    ASSERT_NEAR(std::sqrt(0.5f), p.getNormal().getY(), 0.0001f);
}

TEST_F(Plane_test, NormalAndDistanceValues)
{
    Plane p {
        Vector3 { 1.0f, 1.0f, 1.0f },
        Vector3 { 1.0f, 0.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), 1.0f);
    ASSERT_EQ(p.getNormal(), Vector3(1.0f, 0.0f, 0.0f));

    p = Plane {
        Vector3 { 112.0f, 100.10320f, 1984.0f },
        Vector3 { 100.0f, 0.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.getDistance(), 112.0f);
    ASSERT_FLOAT_EQ(p.getNormal().length(), 1.0f);
}

TEST_F(Plane_test, DistanceToPointOnPlane)
{
    Plane p {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 1.0f, 0.0f, 0.0f }
    };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 0.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 1.0f, 0.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 1.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 1.0f, 2.0f }), 0.0f);
}

TEST_F(Plane_test, DistanceToPointFromOrigoPlane)
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
    Plane p {
        Vector3 { 1.0f, 1.0f, 1.0f },
        Vector3 { 1.0f, 1.0f, 1.0f }
    };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 0.0f }), 0.0f-std::sqrt(3.0f));
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 1.0f, 1.0f, 1.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 2.0f, 2.0f, 2.0f }), std::sqrt(3.0f));

    p = Plane {
        Vector3 { 112.0f, 100.10320f, 1984.0f },
        Vector3 { 100.0f, 0.0f, 0.0f }
    };
    
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 200.0f, 1.0f, 2.0f }), 88.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { -200.0f, 1.0f, 2.0f }), -312.0f);
}


}

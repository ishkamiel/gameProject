#include "math/Plane.h"

#include "math/Vector3.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace pdEngineTest 
{

using Plane = pdEngine::Plane;
using Vector3 = pdEngine::Vector3;

using ::testing::FloatEq;

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

TEST_F(Plane_test, ThreePointConstructor)
{
    Plane v {
        Vector3 {0 ,0, 0},
        Vector3 {1, 0, 0}
    };

    Plane t {
        Vector3 {0 ,1, 0},
        Vector3 {0, 0, 1},
        Vector3 {0, -1, 0}
    };

    ASSERT_EQ(t, v);

    v = {
        Vector3 {0 ,0, 0},
        Vector3 {-1, 0, 0}
    };

    t = {
        Vector3 {0 ,-1, 0},
        Vector3 {0, 0, 1},
        Vector3 {0, 1, 0}
    };

    ASSERT_EQ(t, v);
}

TEST_F(Plane_test, ConstructorsProduceSameVector)
{
    Plane v {
        Vector3 {0 ,0, 0},
        Vector3 {1, 1, 1}
    };

    Plane c { 1, 1, 1, 0 };

    ASSERT_EQ(c, v);
    ASSERT_EQ(c.getNormal(), v.getNormal());
    ASSERT_EQ(c.getDistance(), v.getDistance());

    v = Plane {
        Vector3 {0 ,0, 0},
        Vector3 {123.123f, 134.34f, 1567.567f}
    };

    c = Plane  {123.123f, 134.34f, 1567.567f, 0.0f};

    ASSERT_EQ(c, v);
    ASSERT_EQ(c.getNormal(), v.getNormal());
    ASSERT_EQ(c.getDistance(), v.getDistance());
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

TEST_F(Plane_test, DistanceToPoint3d)
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

TEST_F(Plane_test, DistanceToPointNegativeCoords)
{
    Plane p {
        Vector3 { -1.0f, -1.0f, -1.0f },
        Vector3 { 1.0f, 1.0f, 1.0f }
    };

    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { 0.0f, 0.0f, 0.0f }), std::sqrt(3.0f));
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { -1.0f, -1.0f, -1.0f }), 0.0f);
    ASSERT_FLOAT_EQ(p.distanceTo(Vector3 { -2.0f, -2.0f, -2.0f }), -std::sqrt(3.0f));
    ASSERT_THAT(p.distanceTo(Vector3 { 1.0f, 1.0f, 1.0f }), FloatEq(std::sqrt(12.0f)));
}

TEST_F(Plane_test, IsInside)
{
    Plane p {
        Vector3 { 100.0f, 100.0f, 100.0f },
        Vector3 { 1.0f, 1.0f, 1.0f }
    };

    ASSERT_TRUE(p.isInside(Vector3(1,1,1)));
    ASSERT_TRUE(p.isInside(Vector3(100.0f,100.0f,100.0f)));
    ASSERT_FALSE(p.isInside(Vector3(1000,1000,1000)));

    p = Plane {
        Vector3 { 100.0f, 100.0f, 100.0f },
        Vector3 { -1.0f, -1.0f, -1.0f }
    };

    ASSERT_FALSE(p.isInside(Vector3(1,1,1)));
    ASSERT_TRUE(p.isInside(Vector3(100.0f,100.0f,100.0f)));
    ASSERT_TRUE(p.isInside(Vector3(1000,1000,1000)));

}

TEST_F(Plane_test, IsInsideFrustumFailCheck)
{
    Plane p = Plane {
        Vector3 { 0.0f, 0.0f, 0.0f },
        Vector3 { 0.0f, 0.0f, 1.0f }
    };

    Plane v {0, 0, 1, -0.0f};

    ASSERT_EQ(v, p);
    ASSERT_EQ(v.getNormal(), p.getNormal());

    ASSERT_TRUE(p.isInside(Vector3(0,0,-10)));
}

TEST_F(Plane_test, IsInsideNegativeDirAndDist)
{
    Plane p = Plane {
        Vector3 { 0.0f, 0.0f, -100.0f },
        Vector3 { 0.0f, 0.0f, -1.0f }
    };

    Plane v {0, 0, -1, 100.0f};

    ASSERT_EQ(v, p);
    ASSERT_EQ(v.getNormal(), p.getNormal());

    ASSERT_TRUE(p.isInside(Vector3(0,0,-11)));
}

TEST_F(Plane_test, IsOn)
{
    Plane p {
        Vector3 { 100.0f, 100.0f, 100.0f },
        Vector3 { 1.0f, 1.0f, 1.0f }
    };

    ASSERT_FALSE(p.isOn(Vector3(1,1,1)));
    ASSERT_TRUE(p.isOn(Vector3(100.0f,100.0f,100.0f)));
    ASSERT_FALSE(p.isOn(Vector3(1000,1000,1000)));

    p = Plane {
        Vector3 { 10.0f, 10.0f, 10.0f },
        Vector3 { 1.0f, 1.0f, 0.0f }
    };


    ASSERT_TRUE(p.isOn(Vector3(11.0f,9.0f,0.0f)));
}

}

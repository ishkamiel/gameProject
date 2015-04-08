#include "math/Plane_fwd.h"

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
    //Vector3 vec0 { 0.0f, 0.0f, 0.0f };
    //Vector3 vec11 { 1.0f, 0.0f, 0.0f };
    //Plane coords { 1.0f, 0.0f, 0.0f, 0.0f };
    //Plane vecs { vec0, vec11 };
    //ASSERT_EQ(coords, vecs);
}

}

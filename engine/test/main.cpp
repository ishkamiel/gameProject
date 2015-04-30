#include "gtest/gtest.h"
#include "gmock/gmock.h"

class pdeEnvironment : public ::testing::Environment
{
 public:
  virtual ~pdeEnvironment() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

int main(int argc, char** argv) {
    ::testing::Environment* const foo_env = ::testing::AddGlobalTestEnvironment(new pdeEnvironment());

    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}

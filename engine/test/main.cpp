#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

class pdeEnvironment : public ::testing::Environment
{
 public:
  virtual ~pdeEnvironment() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

int main(int argc, char** argv) {
    ::testing::AddGlobalTestEnvironment(new pdeEnvironment());

    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}

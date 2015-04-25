#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "app/Config.h"

namespace pdEngine
{

class Config_test : public ::testing::Test
{

protected:
	Config_test();

	virtual ~Config_test();

	virtual void SetUp();

	virtual void TearDown();
};

}
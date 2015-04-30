#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "utils/Logger.h"

namespace pdEngine
{

class test_Logger : public ::testing::Test
{
protected:

	static void SetUpTestCase()
	{ }

	virtual void SetUp()
	{ }

	virtual void TearDown()
	{ }
};

TEST_F(test_Logger, canSetLogLevel)
{
	ASSERT_NO_THROW(setGlobalLogLevel(LogLevel::trace));
	ASSERT_NO_THROW(setGlobalLogLevel(LogLevel::fatal));
}

}


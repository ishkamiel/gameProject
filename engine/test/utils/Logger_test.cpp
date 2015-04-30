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

TEST_F(test_Logger, exitFailureExits)
{
	auto myFailer = []() {
	    PDE_EXIT_FAILURE("test failure");
	};

	ASSERT_DEATH(myFailer(), "test failure");
}

TEST_F(test_Logger, fatalNotImplemented)
{
	auto notImplemented = []() {
	    PDE_NOT_IMPLEMENTED_FATAL();
	};

	ASSERT_DEATH(notImplemented(), "not implemented");
}

}


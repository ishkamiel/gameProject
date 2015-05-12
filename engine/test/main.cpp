#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "app/Config.h"
#include "utils/Logger.h"

#include <memory>

class pdeEnvironment : public ::testing::Environment
{
public:
	virtual ~pdeEnvironment() {}

	virtual void SetUp() {
		pdEngine::setGlobalLogLevel(pdEngine::LogLevel::none);
		pdEngine::Config::get()->init();
	}

	virtual void TearDown() {}
};

int main(int argc, char** argv) {
    ::testing::AddGlobalTestEnvironment(new pdeEnvironment());
	::testing::FLAGS_gtest_death_test_style = "threadsafe";

    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}

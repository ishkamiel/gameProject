#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "app/Config.h"
#include "utils/Logger.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

#define TEST_CONFIG "testing.config"

namespace pdEngine
{

namespace fs = boost::filesystem;
namespace po = boost::program_options;

::testing::AssertionResult ConfigInitOk(bool ok)
{
	return ok ?  ::testing::AssertionSuccess()
			: ::testing::AssertionFailure() << "Config->init has failed, probably due to engine "
	<< "config file [" << PDE_BUILDOPT_CONFIG_DIR << "/" <<PDE_BUILDOPT_CONFIG_FILENAME << "]";
}

class test_Config: public ::testing::Test
{
protected:
	const std::string tvar_NE = "abcdefghijklmnopqrstuvw.thereCanBeOnlyONE";
	const std::string tvar_engine = "engine.name";
	const std::string tval_engine = "pdEngine";

	const std::string tvar_float = "testing.floating";
	const float tval_float = 0.123f;

	const std::string tvar_int = "testing.integer";
	const int tval_int = 123;

	static void SetUpTestCase()
	{
		setGlobalLogLevel(LogLevel::trace);

		auto conf = Config::get();

		if (!conf->isInitialized()) {
			po::options_description testOpts("Testing config");
			testOpts.add_options()
				("testing.floating", po::value<float>())
				("testing.integer", po::value<int>());

			conf->getOptionDescriptor()->add(testOpts);

			ASSERT_TRUE(ConfigInitOk(conf->init()));

			ASSERT_TRUE(conf->addConfigFile(TEST_CONFIG, false));
		}
	}

	virtual void SetUp()
	{ }

	virtual void TearDown()
	{}
};

/*
TEST_F(test_Config, GetsCorrectProgramPath)
{
	auto conf = Config::get();

	ASSERT_NE("", conf->getRootPath());
}
*/

/*
TEST_F(test_Config, InitializationWorks)
{
	auto conf = Config::get();

	ASSERT_TRUE(conf->init());
}
*/

TEST_F(test_Config, hasVariableSeemsToFindValues)
{
	auto conf = Config::get();

	ASSERT_TRUE(conf->hasVariable(tvar_engine));
}

TEST_F(test_Config, GetterAndValues)
{
	auto conf = Config::get();

	ASSERT_EQ(conf->getString(tvar_engine), tval_engine);
}

TEST_F(test_Config, AddedConfigFindsInt)
{
	auto conf = Config::get();

	ASSERT_EQ(conf->getInt(tvar_int), tval_int);
}

TEST_F(test_Config, AddedConfigFindsFloat)
{
	auto conf = Config::get();

	ASSERT_EQ(conf->getFloat(tvar_float), tval_float);
}

TEST_F(test_Config, EngineConfigAccessibleAfterConfigAdd)
{
	auto conf = Config::get();

	ASSERT_EQ(conf->getString(tvar_engine), tval_engine);
}


TEST_F(test_Config, GetterWithDefaultValues)
{
	auto conf = Config::get();

	ASSERT_FALSE(conf->hasVariable(tvar_NE));

	ASSERT_EQ(conf->getString(tvar_NE, "myDefaultThingy"), "myDefaultThingy");
	ASSERT_EQ(conf->getInt(tvar_NE, 98765), 98765);
	ASSERT_EQ(conf->getFloat(tvar_NE, 0.999f), 0.999f);
	//ASSERT_TRUE(conf->getBool(tvar_NE, true));
	//ASSERT_FALSE(conf->getBool(tvar_NE, false));
}

}
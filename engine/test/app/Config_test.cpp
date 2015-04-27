#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "app/Config.h"
#include "utils/Logger.h"

#include <boost/filesystem.hpp>

namespace pdEngine
{

namespace fs = boost::filesystem;


class test_Config: public ::testing::Test
{

protected:

	virtual void SetUp()
	{
		setGlobalLogLevel(LogLevel::fatal);
		Config::get()->reset();
		Config::get()->init();
	}

	virtual void TearDown()
	{
		Config::get()->reset();
	}
};

TEST_F(test_Config, GetsCorrectProgramPath)
{
	auto conf = Config::get();

	ASSERT_NE("", conf->getRootPath());
}

TEST_F(test_Config, InitializationWorks)
{
	auto conf = Config::get();
	conf->reset();

	ASSERT_TRUE(conf->init());
	PDE_TRACE << "InitializationWorks test done";
}

TEST_F(test_Config, FindsEngineConfigFile)
{
	auto conf = Config::get();

	/*
	auto configFile = fs::current_path();
	configFile /= "config";
	configFile /= "engine.conf";

	conf->addConfigFile(configFile.string());
	 */

	ASSERT_TRUE(conf->foundEngineConfig());
}

TEST_F(test_Config, GetterAndValues)
{
	auto conf = Config::get();

	auto val = conf->get("pdEngine/name");
	ASSERT_EQ(val, "pdEngine");
}

TEST_F(test_Config, FindsAddedConfigfile)
{
	auto conf = Config::get();

	auto configFile = fs::current_path();
	configFile /= "config";
	configFile /= "engine.conf";

	ASSERT_TRUE(conf->addConfigFile(configFile.string()));
}

TEST_F(test_Config, GetterWithDefaultValues)
{
	// TODO
}

}
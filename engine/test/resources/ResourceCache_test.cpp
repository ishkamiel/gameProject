#include "resources/ResourceCache.h"

#include "app/Config.h"
#include "resources/DirectoryContainer.h"
#include "resources/DefaultResourceLoader.h"
#include "utils/Logger.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#define CONFIG_FILE "DirectoryContainer_test.config"
#define RES_CONFIG "DirectoryContainer_test.resource_path"

namespace pdEngine
{

class test_ResourceCache : public ::testing::Test
{
protected:
	std::shared_ptr<ResourceCache> m_resourceCache;

	static void SetUpTestCase()
	{
		setGlobalLogLevel(LogLevel::none);

		boost::program_options::options_description desc;
		desc.add_options()
			(RES_CONFIG, boost::program_options::value<std::string>());

		auto conf = Config::get();
		if (!conf->isInitialized()) ASSERT_TRUE(conf->init());
		conf->getOptionDescriptor()->add(desc);

		ASSERT_TRUE(conf->addConfigFile(CONFIG_FILE, false));
		ASSERT_NE(conf->getString(RES_CONFIG), "");
	}

	static void TearDownTestCase()
	{ }

	virtual void SetUp()
	{
		m_resourceCache.reset(new ResourceCache(100));
		m_resourceCache->registerLoader(ResourceLoader_sptr(new DefaultResourceLoader()));

		boost::filesystem::path path{Config::get()->getRootDirectoryPath()};

		path /= Config::get()->getString("resources.root");
		path /= Config::get()->getString(RES_CONFIG);

		auto container = std::make_shared<DirectoryContainer>(path.string());
		ASSERT_TRUE(m_resourceCache->addContainer(container));
	};

	virtual void TearDown()
	{ }
};

TEST_F(test_ResourceCache, doNothing)
{
	ASSERT_TRUE(true);
}

}
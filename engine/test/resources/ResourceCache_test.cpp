#include "resources/ResourceCache.h"

#include "app/Config.h"
#include "resources/DirectoryContainer.h"
#include "resources/DefaultResourceLoader.h"
#include "utils/Logger.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#define RES_CONTAINER   "testResourceDir"
#define RES_FILETXT     "testResourceDir/file.txt"
#define RES_SUBDIRFILE "testResouceDir/subDirectory/subDirFile.txt"

namespace pdEngine
{

class test_ResourceCache : public ::testing::Test
{
protected:
	std::shared_ptr<ResourceCache> m_resourceCache;

	static void SetUpTestCase()
	{
		setGlobalLogLevel(LogLevel::trace);
	}

	static void TearDownTestCase()
	{ }

	virtual void SetUp()
	{
		m_resourceCache.reset(new ResourceCache(100));
		m_resourceCache->registerLoader(ResourceLoader_sptr(new DefaultResourceLoader()));

		boost::filesystem::path path{Config::get()->getRootDirectoryPath()};

		path /= Config::get()->getString("resources.root");
		path /= RES_CONTAINER;

		auto container = std::make_shared<DirectoryContainer>(path.string());
		ASSERT_TRUE(m_resourceCache->addContainer(container));
	};

	virtual void TearDown()
	{ }
};

TEST_F(test_ResourceCache, getHandleReturnsSomething)
{
	auto r = std::make_shared<Resource>(RES_FILETXT);
	auto h = m_resourceCache->getHandle(r);
	ASSERT_FALSE(!h);
	PDE_TRACE << "Ookay...";
}

}
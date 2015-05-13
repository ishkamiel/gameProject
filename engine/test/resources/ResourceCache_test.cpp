#include "resources/ResourceCache.h"

#include "app/Config.h"
#include "resources/DirectoryContainer.h"
#include "resources/DefaultResourceLoader.h"
#include "utils/Logger.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <cstring>

#define RES_CONTAINER   "testResourceDir"
#define RES_FILETXT     "testResourceDir/file.txt"
#define RES_SUBDIRFILE "testResourceDir/subdirectory/subdirfile.txt"
#define EXPECTED_FILETXT "line1\nline2\nline3"
#define EXPECTED_SUBDIRFILE "first line, aaa\nsecond line, bbb\n"

namespace pdEngine
{

class test_ResourceCache : public ::testing::Test
{
protected:
	std::shared_ptr<ResourceCache> m_resourceCache;

	static void SetUpTestCase()
	{
		setGlobalLogLevel(LogLevel::none);
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

TEST_F(test_ResourceCache, getHandleCorrectlyReadsOneResource)
{
	auto r = std::make_shared<Resource>(RES_FILETXT);
	auto h = m_resourceCache->getHandle(r);
	ASSERT_FALSE(!h);
	PDE_TRACE << "Ookay...";

	ASSERT_THAT(!h, false);
	ASSERT_THAT(std::string(h->getBuffer(), h->getSize()), std::string(EXPECTED_FILETXT));
}

TEST_F(test_ResourceCache, getHandleCorreclyLoadsResourceWithLongerPath)
{
	auto r2 = std::make_shared<Resource>(RES_SUBDIRFILE);
	auto h2 = m_resourceCache->getHandle(r2);
	ASSERT_THAT(!h2, false);
	ASSERT_THAT(std::string(h2->getBuffer(), h2->getSize()), std::string(EXPECTED_SUBDIRFILE));
}

TEST_F(test_ResourceCache, multipleResourcesLoaded)
{
	auto r1 = std::make_shared<Resource>(RES_FILETXT);
	auto r2 = std::make_shared<Resource>(RES_SUBDIRFILE);
	auto h1 = m_resourceCache->getHandle(r1);
	auto h2 = m_resourceCache->getHandle(r2);

	ASSERT_THAT(std::string(h1->getBuffer(), h1->getSize()), std::string(EXPECTED_FILETXT));
	ASSERT_THAT(!h2, false);
	ASSERT_THAT(std::string(h2->getBuffer(), h2->getSize()), std::string(EXPECTED_SUBDIRFILE));
}


}
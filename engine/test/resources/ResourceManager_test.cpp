#include "resources/ResourceManager.h"

#include "app/Config.h"
#include "resources/ResourceHandle.h"
#include "tasks/Task.h"
#include "utils/Logger.h"

#include "pugixml.hpp"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstring>

#define RES_XMLDOC "testResourceDir/subdirectory/xml_document.xml"
#define RES_CONTAINER "testResourceDir"
#define RES_FILETXT "testResourceDir/file.txt"
#define RES_SUBDIRFILE "testResourceDir/subdirectory/subdirfile.txt"
#define EXPECTED_FILETXT "line1\nline2\nline3"
#define EXPECTED_SUBDIRFILE "first line, aaa\nsecond line, bbb\n"

namespace pdEngine
{

class test_ResourceManager : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{
		//setGlobalLogLevel(LogLevel::all);

		auto rm = ResourceManager::get();
		ASSERT_FALSE(!rm);

		auto rm_task = std::static_pointer_cast<Task>(rm);
		if (rm_task->isUninitialized()) {
			rm_task->onInit();
		}
		ASSERT_FALSE(rm_task->isUninitialized());

		ASSERT_TRUE(rm->addContainer("testResourceDir"));
	}

	static void TearDownTestCase()
	{ }

	virtual void SetUp()
	{ }

	virtual void TearDown()
	{ }
};

TEST_F(test_ResourceManager, loadsRawFiles)
{
	auto rm = ResourceManager::get();

	auto h_file = rm->loadResource(RES_FILETXT);
	ASSERT_THAT(std::string(h_file->getBuffer(), h_file->getSize()),
	            std::string(EXPECTED_FILETXT));

	auto h_subfile = rm->loadResource(RES_SUBDIRFILE);
	ASSERT_THAT(std::string(h_subfile->getBuffer(), h_subfile->getSize()),
	            std::string(EXPECTED_SUBDIRFILE));
}

TEST_F(test_ResourceManager, loadsXML)
{
	auto rm = ResourceManager::get();
	auto xml = rm->loadXML(RES_XMLDOC);

	ASSERT_FALSE(!xml);
	ASSERT_THAT((std::string)xml->first_child().name(), std::string("testingDocument"));
}

}
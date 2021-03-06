#include "resources/DirectoryContainer.h"

#include "app/Config.h"
#include "utils/Logger.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <boost/program_options.hpp>

#define CONFIG_FILE "DirectoryContainer_test.config"
#define RES_CONFIG "DirectoryContainer_test.resource_path"

namespace pdEngine
{

using ::testing::Gt;

class test_DirectoryContainer : public ::testing::Test
{
protected:
	std::string m_resourcePath;
	std::shared_ptr<I_ResourceContainer> m_container;

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
	    boost::filesystem::path path{Config::get()->getRootDirectoryPath()};

	    path /= Config::get()->getString("resources.root");
	    path /= Config::get()->getString(RES_CONFIG);
	    m_resourcePath = path.string();
	    m_container = std::make_shared<DirectoryContainer>(m_resourcePath);
    };

    virtual void TearDown()
    { }
};

TEST_F(test_DirectoryContainer, testConstructorWithExisting)
{
	ASSERT_NO_THROW(DirectoryContainer cont(m_resourcePath));
}

TEST_F(test_DirectoryContainer, testConstructorOkWithMakeShared)
{
	ASSERT_NO_THROW(m_container = std::make_shared<DirectoryContainer>(m_resourcePath));
}


TEST_F(test_DirectoryContainer, testConstructorsWithNonExisting)
{
    ASSERT_NO_THROW(DirectoryContainer cont("adlfjasdlkfj kdsghalköshdlkhsdkhalökfhlask"));
}

TEST_F(test_DirectoryContainer, containerNameCorrectlyReturned)
{
	auto rName = Config::get()->getString(RES_CONFIG);
	std::transform(rName.begin(), rName.end(), rName.begin(), ::tolower);
	ASSERT_THAT(m_container->v_getName(), rName);
}

TEST_F(test_DirectoryContainer, seemsToOpenExistingDirectory)
{
	DirectoryContainer cont{m_resourcePath};

	ASSERT_TRUE(cont.v_open());
}

TEST_F(test_DirectoryContainer, findsStuffInOpenedDirectory)
{
	m_container->v_open();

	// Use Gt to allow for added testing resources.
	ASSERT_THAT(m_container->v_getResourceCount(), Gt(2));
}

TEST_F(test_DirectoryContainer, findsAndReturnsSizeForResource)
{
	m_container->v_open();
	Resource r{"testResourceDir/file.txt"};

	ASSERT_THAT(m_container->v_getRawResourceSize(&r), Gt(0));
}

TEST_F(test_DirectoryContainer, seemsToLoadRawResource)
{
	m_container->v_open();
	Resource r{"testResourceDir/file.txt"};

	auto size = m_container->v_getRawResourceSize(&r);
	char buffer[size];

	ASSERT_THAT(m_container->v_loadRawResource(&r, buffer), size);
}

TEST_F(test_DirectoryContainer, loadedResourceProperlyAccessible)
{
	m_container->v_open();
	Resource r{"testResourceDir/file.txt"};

	auto size = m_container->v_getRawResourceSize(&r);
	char *buffer = new char[size+1];
	m_container->v_loadRawResource(&r, buffer);

	buffer[size] = '\0';
	std::string expected = "line1\nline2\nline3";

	ASSERT_THAT(std::string(buffer), expected);
}

TEST_F(test_DirectoryContainer, loadsResourceInSubdirectory)
{
	m_container->v_open();
	Resource r{"testResourceDir/subdirectory/subdirfile.txt"};

	ASSERT_THAT(m_container->v_getRawResourceSize(&r), Gt(0));

	auto size = m_container->v_getRawResourceSize(&r);
	char *buffer = new char[size];
	m_container->v_loadRawResource(&r, buffer);

	ASSERT_THAT(std::string(buffer, size),
	            std::string("first line, aaa\nsecond line, bbb\n"));
}

}

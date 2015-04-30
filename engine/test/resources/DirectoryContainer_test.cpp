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

class test_DirectoryContainer : public ::testing::Test
{
protected:
    std::string m_ResourcePath;

    static void SetUpTestCase() {
		//setGlobalLogLevel(LogLevel::trace);

        boost::program_options::options_description desc;
        desc.add_options()
            (RES_CONFIG, boost::program_options::value<std::string>());

        auto conf = Config::get();
        conf->getOptionDescriptor()->add(desc);

        ASSERT_TRUE(conf->addConfigFile(CONFIG_FILE, false));
        ASSERT_NE(conf->getString(RES_CONFIG), "");
    }

    static void TearDownTestCase() {}

    virtual void SetUp()
    {
        m_ResourcePath = Config::get()->getString(RES_CONFIG);
    }

    virtual void TearDown()
    {}
};

TEST_F(test_DirectoryContainer, testConstructorWithExisting)
{
    ASSERT_NO_THROW(DirectoryContainer cont(m_ResourcePath));
}

TEST_F(test_DirectoryContainer, testConstructorsWithNonExisting)
{
    ASSERT_NO_THROW(DirectoryContainer cont("adlfjasdlkfj kdsghalköshdlkhsdkhalökfhlask"));
}

}

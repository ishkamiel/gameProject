#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "resources/SimpleResourceFile.h"
#include "resources/Resource.h"
#include "utils/Memory.h"

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <cassert>
#include <sstream>
#include <stdlib.h>

namespace pdEngine
{

class SimpleResourceFile_test : public ::testing::Test
{
protected:
    std::string fn_ef;
    std::string fn_ne;
    std::string fn_bin123;

    std::string tmpDir;

    SimpleResourceFile_test()
    {};

    virtual ~SimpleResourceFile_test()
    {};

	virtual std::string getFilename(std::string s)
	{
        std::stringstream ss;
		ss << tmpDir << "/" << s;
		return ss.str();
	}

    virtual void SetUp()
    {
		char tc[] = "testXXXXXX";
        tmpDir = mkdtemp(tc);

        fn_ef = getFilename("emptyFile");
        fn_bin123 = getFilename("bin123");

        assert(fn_ef != fn_ne
               && fn_ef != fn_bin123
               && fn_ne != fn_bin123);

        std::ofstream file;

        // create empty file
        file.open(fn_ef);
        if (file.is_open())
        {
            file.close();
        }
        else
        {
            std::cerr << "Unable to create file: " << fn_ef << "\n";
        }

        // create file with 123 bytes
        file.open(fn_bin123);
        if (file.is_open())
        {
            char *outbuffer = new char[123];

            for (auto i = 0; i < 123; ++i)
            {
                outbuffer[i] = (char) i;
            }
            file.write(outbuffer, 123);
            delete[] outbuffer;
            file.close();
        }
        else
        {
            std::cerr << "Unable to create file: " << fn_bin123 << "\n";
        }
    }

    virtual void TearDown()
    {
        std::remove(fn_ne.c_str());
        std::remove(fn_ef.c_str());
        std::remove(fn_bin123.c_str());

        if (rmdir(tmpDir.c_str()) != 0)
        {
            std::cerr << "Unable to remove temporary directory "
                    << tmpDir << ": " << strerror(errno) << "\n";
        }
    };
};

/*
TEST_F(SimpleResourceFile_test, testConstructors)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ne);
    srf.reset(new pdEngine::SimpleResourceFile(fn_ef));
    srf.reset(new pdEngine::SimpleResourceFile(fn_bin123));
}

TEST_F(SimpleResourceFile_test, vOpen)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    ASSERT_TRUE(srf->v_open());
}

TEST_F(SimpleResourceFile_test, vGetNumResources)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    ASSERT_TRUE(srf->v_open());
    ASSERT_EQ(srf->v_getResourceCount(), 1);
}

TEST_F(SimpleResourceFile_test, vGetResourceName)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    auto res = pdEngine::Resource(fn_bin123);
    ASSERT_TRUE(srf->v_open());
    ASSERT_EQ(srf->v_getResourceName(0), res.getName());
}

TEST_F(SimpleResourceFile_test, vGetRawResourceSize)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    auto res = std::make_shared<Resource>(fn_bin123);
    srf->v_open();
    ASSERT_EQ(srf->v_getRawResourceSize(res), 123);
}

TEST_F(SimpleResourceFile_test, vGetRawResource)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    auto res = std::make_shared<Resource>(fn_bin123);
    srf->v_open();

    char* buffer = new char[srf->v_getRawResourceSize(res)];

    ASSERT_EQ(srf->v_loadRawResource(res, buffer), 123);
    ASSERT_EQ(buffer[120], (char) 120);
    ASSERT_EQ(buffer[0], (char) 0);

    pdEngine::safeDeleteArray(buffer);
}

TEST_F(SimpleResourceFile_test, EmptyFile)
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ef);
    ASSERT_TRUE(srf->v_open());
}

TEST_F(SimpleResourceFile_test, NonExistingFile)
{
    // non-existing file cannot be opened
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ne);
    ASSERT_FALSE(srf->v_open());
    ASSERT_THROW(srf->v_getResourceCount(), std::logic_error);

    auto res = pdEngine::Resource(fn_ne);

    ASSERT_THROW(srf->v_getRawResourceSize(res), std::logic_error);

    char b[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    ASSERT_THROW(srf->v_loadRawResource(res, b), std::logic_error);
    ASSERT_EQ(1, b[0]);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[9], 0);

    ASSERT_THROW(srf->v_getResourceName(0), std::logic_error);
    ASSERT_THROW(srf->v_getResourceName(100), std::logic_error);
    ASSERT_THROW(srf->v_getResourceName(10), std::logic_error);
}


//
// void SimpleResourceFile_test::t_Constructor()
// {
//     using srf = pdEngine::SimpleResourceFile;
//     CPPUNIT_ASSERT(true);
// }
//
//
// void SimpleResourceFile_test::t_vOpen() 
// {
//     using srf = pdEngine::SimpleResourceFile;
//
//     CPPUNIT_ASSERT(srf_ef->v_open());
//     CPPUNIT_ASSERT(!srf_ne->v_open());
//     CPPUNIT_ASSERT(srf_bin123->v_open());
// }
//
// void SimpleResourceFile_test::t_vGetRawResourceSize() 
// {
//     using srf = pdEngine::SimpleResourceFile;
//     using res = pdEngine::Resource;
//
//     CPPUNIT_ASSERT_EQUAL(srf_ef->v_getRawResourceSize(*res_ef), 0);
//     CPPUNIT_ASSERT_EQUAL(srf_ne->v_getRawResourceSize(*res_ne), 0);
//     CPPUNIT_ASSERT_EQUAL(srf_bin123->v_getRawResourceSize(*res_bin123), 123);
// }
//
// void SimpleResourceFile_test::t_vGetNumResources()
// {
//     // CPPUNIT_ASSERT_EQUAL(srf_ne->v_getResourceCount(*res_ne), 0);
//     // CPPUNIT_ASSERT_EQUAL(srf_ef->v_getResourceCount(*res_ef), 1);
//     // CPPUNIT_ASSERT_EQUAL(srf_bin123->v_getResourceCount(*res_bin123), 1);
// }
//
// void SimpleResourceFile_test::t_vGetResourceName()
// {
//     // CPPUNIT_ASSERT_EQUAL(srf_ne->v_getResourceCount(*res_ne), 0);
//     // CPPUNIT_ASSERT_EQUAL(srf_ef->v_getResourceCount(*res_ef), 1);
//     // CPPUNIT_ASSERT_EQUAL(srf_bin123->v_getResourceCount(*res_bin123), 1);
// }
 */
}

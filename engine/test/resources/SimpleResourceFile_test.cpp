#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "resources/SimpleResourceFile.h"
#include "resources/Resource.h"

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <cassert>

class SimpleResourceFile_test : public ::testing::Test 
{
protected:
    std::string fn_ef;
    std::string fn_ne;
    std::string fn_bin123;

    SimpleResourceFile_test() {
        fn_ef = std::string(std::tmpnam(nullptr));
        fn_ne = std::string(std::tmpnam(nullptr));
        fn_bin123 = std::string(std::tmpnam(nullptr));
    };

    virtual ~SimpleResourceFile_test()
    {
    };

    virtual void SetUp()
    {
        assert(fn_ef != fn_ne
                && fn_ef != fn_bin123
                && fn_ne != fn_bin123);

        std::ofstream file;

        { // create empty file
            file.open(fn_ef);
            file.close();
        }

        { // create file with 123 bytes
            file.open(fn_bin123);
            for (auto i = 1; i < 124; ++i)
            {
                file << (char)i;
            }
            file.close();
        }
        
        // srf_ef.reset(new pdEngine::SimpleResourceFile(*fn_ef));
        // srf_ne.reset(new pdEngine::SimpleResourceFile(*fn_ne));
        // srf_bin123.reset(new pdEngine::SimpleResourceFile(*fn_bin123));
        //
        // res_ef.reset(new pdEngine::Resource(*fn_ef));
        // res_ne.reset(new pdEngine::Resource(*fn_ne));
        // res_bin123.reset(new pdEngine::Resource(*fn_bin123));
    };

    virtual void TearDown()
    {
        std::remove(fn_ne.c_str());
        std::remove(fn_ef.c_str());
        std::remove(fn_bin123.c_str());
    };
};

TEST_F(SimpleResourceFile_test, testConstructors) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ne);
    srf.reset(new pdEngine::SimpleResourceFile(fn_ef));
    srf.reset(new pdEngine::SimpleResourceFile(fn_bin123));
}

TEST_F(SimpleResourceFile_test, vOpen) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    ASSERT_TRUE(srf->vOpen());
}

TEST_F(SimpleResourceFile_test, vGetNumResources) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    ASSERT_TRUE(srf->vOpen());
    ASSERT_EQ(srf->vGetNumResources(), 1);
}

TEST_F(SimpleResourceFile_test, vGetResourceName) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    ASSERT_TRUE(srf->vOpen());
    ASSERT_EQ(srf->vGetResourceName(0), fn_bin123);
}

TEST_F(SimpleResourceFile_test, vGetRawResourceSize) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    auto res = pdEngine::Resource(fn_bin123);
    srf->vOpen();

    ASSERT_EQ(srf->vGetRawResourceSize(res), 123);
}

TEST_F(SimpleResourceFile_test, vGetRawResource) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_bin123);
    auto res = pdEngine::Resource(fn_bin123);
    srf->vOpen();
    char* buffer = new char[srf->vGetRawResourceSize(res)];

    ASSERT_EQ(srf->vGetRawResource(res, buffer), 123);
    ASSERT_EQ(buffer[120], 121);
    ASSERT_EQ(buffer[0], 1);

    delete buffer;
}

TEST_F(SimpleResourceFile_test, EmptyFile) 
{
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ef);
    ASSERT_TRUE(srf->vOpen());
}

TEST_F(SimpleResourceFile_test, NonExistingFile) 
{
    // non-existing file cannot be opened
    auto srf = std::make_shared<pdEngine::SimpleResourceFile>(fn_ne);
    ASSERT_FALSE(srf->vOpen());
    ASSERT_THROW(srf->vGetNumResources(), std::logic_error);

    auto res = pdEngine::Resource(fn_ne);

    ASSERT_THROW(srf->vGetRawResourceSize(res), std::logic_error);

    char b[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    ASSERT_THROW(srf->vGetRawResource(res, b), std::logic_error);
    ASSERT_EQ(1, b[0]);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[9], 0);

    ASSERT_THROW(srf->vGetResourceName(0), std::logic_error);
    ASSERT_THROW(srf->vGetResourceName(100), std::logic_error);
    ASSERT_THROW(srf->vGetResourceName(10), std::logic_error);
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
//     CPPUNIT_ASSERT(srf_ef->vOpen());
//     CPPUNIT_ASSERT(!srf_ne->vOpen());
//     CPPUNIT_ASSERT(srf_bin123->vOpen());
// }
//
// void SimpleResourceFile_test::t_vGetRawResourceSize() 
// {
//     using srf = pdEngine::SimpleResourceFile;
//     using res = pdEngine::Resource;
//
//     CPPUNIT_ASSERT_EQUAL(srf_ef->vGetRawResourceSize(*res_ef), 0);
//     CPPUNIT_ASSERT_EQUAL(srf_ne->vGetRawResourceSize(*res_ne), 0);
//     CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetRawResourceSize(*res_bin123), 123);
// }
//
// void SimpleResourceFile_test::t_vGetNumResources()
// {
//     // CPPUNIT_ASSERT_EQUAL(srf_ne->vGetNumResources(*res_ne), 0);
//     // CPPUNIT_ASSERT_EQUAL(srf_ef->vGetNumResources(*res_ef), 1);
//     // CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetNumResources(*res_bin123), 1);
// }
//
// void SimpleResourceFile_test::t_vGetResourceName()
// {
//     // CPPUNIT_ASSERT_EQUAL(srf_ne->vGetNumResources(*res_ne), 0);
//     // CPPUNIT_ASSERT_EQUAL(srf_ef->vGetNumResources(*res_ef), 1);
//     // CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetNumResources(*res_bin123), 1);
// }

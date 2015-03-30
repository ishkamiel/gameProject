#include "resources/SimpleResourceFile_test.h"

#include <cstdio>
#include <fstream>


void SimpleResourceFile_test::setUp(void) 
{
    std::ofstream file;

    // create empty file
    fn_ef.reset(new str(std::tmpnam(nullptr)));

    file.open(*fn_ef);
    file.close();

    // create file with 123 bytes
    fn_bin123.reset(new str(std::tmpnam(nullptr)));

    file.open(*fn_bin123);
    for (auto i = 1; i < 124; ++i)
    {
        file << (char)i;
    }
    file.close();

    // just get a guaranteed non-existing filename
    fn_ne.reset(new str(std::tmpnam(nullptr)));

    srf_ef.reset(new pdEngine::SimpleResourceFile(*fn_ef));
    srf_ne.reset(new pdEngine::SimpleResourceFile(*fn_ne));
    srf_bin123.reset(new pdEngine::SimpleResourceFile(*fn_bin123));

    res_ef.reset(new pdEngine::Resource(*fn_ef));
    res_ne.reset(new pdEngine::Resource(*fn_ne));
    res_bin123.reset(new pdEngine::Resource(*fn_bin123));
}

void SimpleResourceFile_test::tearDown(void) 
{
    std::remove(fn_ef->c_str());
    std::remove(fn_bin123->c_str());
}

void SimpleResourceFile_test::t_Constructor()
{
    using srf = pdEngine::SimpleResourceFile;
    CPPUNIT_ASSERT(true);
}


void SimpleResourceFile_test::t_vOpen() 
{
    using srf = pdEngine::SimpleResourceFile;

    CPPUNIT_ASSERT(srf_ef->vOpen());
    CPPUNIT_ASSERT(!srf_ne->vOpen());
    CPPUNIT_ASSERT(srf_bin123->vOpen());
}

void SimpleResourceFile_test::t_vGetRawResourceSize() 
{
    using srf = pdEngine::SimpleResourceFile;
    using res = pdEngine::Resource;

    CPPUNIT_ASSERT_EQUAL(srf_ef->vGetRawResourceSize(*res_ef), 0);
    CPPUNIT_ASSERT_EQUAL(srf_ne->vGetRawResourceSize(*res_ne), 0);
    CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetRawResourceSize(*res_bin123), 123);
}

void SimpleResourceFile_test::t_vGetNumResources()
{
    // CPPUNIT_ASSERT_EQUAL(srf_ne->vGetNumResources(*res_ne), 0);
    // CPPUNIT_ASSERT_EQUAL(srf_ef->vGetNumResources(*res_ef), 1);
    // CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetNumResources(*res_bin123), 1);
}

void SimpleResourceFile_test::t_vGetResourceName()
{
    // CPPUNIT_ASSERT_EQUAL(srf_ne->vGetNumResources(*res_ne), 0);
    // CPPUNIT_ASSERT_EQUAL(srf_ef->vGetNumResources(*res_ef), 1);
    // CPPUNIT_ASSERT_EQUAL(srf_bin123->vGetNumResources(*res_bin123), 1);
}

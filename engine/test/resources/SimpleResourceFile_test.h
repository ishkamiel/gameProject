#include <cppunit/extensions/HelperMacros.h>

#include "resources/SimpleResourceFile.h"
#include "resources/Resource.h"

#include <memory>

class SimpleResourceFile_test : public CppUnit::TestFixture
{
    using srf = std::shared_ptr<pdEngine::SimpleResourceFile>;
    using res = std::shared_ptr<pdEngine::Resource>;
    using str = std::shared_ptr<std::string>;

    CPPUNIT_TEST_SUITE(SimpleResourceFile_test);
    CPPUNIT_TEST(t_Constructor);
    CPPUNIT_TEST(t_vOpen);
    CPPUNIT_TEST(t_vGetRawResourceSize);
    CPPUNIT_TEST(t_vGetNumResources);
    CPPUNIT_TEST(t_vGetResourceName);
    CPPUNIT_TEST(t_Constructor);
    CPPUNIT_TEST_SUITE_END();

    str fn_ne;
    str fn_ef;
    str fn_bin123;

    srf srf_ne;
    srf srf_ef;
    srf srf_bin123;

    res res_ne;
    res res_ef;
    res res_bin123;

public:
    void setUp(void);
    void tearDown(void);

protected:
    void t_Constructor();
    void t_vOpen();
    void t_vGetRawResourceSize();
    void t_vGetNumResources();
    void t_vGetResourceName();
};

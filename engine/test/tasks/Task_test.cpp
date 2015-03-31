#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tasks/Task.h"

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <cassert>

class Task_test : public ::testing::Test 
{
protected:
    std::string fn_ef;
    std::string fn_ne;
    std::string fn_bin123;

    Task_test() {
        fn_ef = std::string(std::tmpnam(nullptr));
        fn_ne = std::string(std::tmpnam(nullptr));
        fn_bin123 = std::string(std::tmpnam(nullptr));
    };

    virtual ~Task_test()
    {
    };

    virtual void SetUp()
    {
    };

    virtual void TearDown()
    {
    };
};

TEST_F(Task_test, testConstructors) 
{
}

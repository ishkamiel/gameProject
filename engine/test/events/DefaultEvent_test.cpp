#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events/DefaultEvent.h"

#include <cstring>

class DefaultEvent_test : public ::testing::Test 
{
protected:
    // DefaultEvent_test();
    // virtual ~DefaultEvent_test();
    //
    // virtual void SetUp();
    // virtual void TearDown();
};


TEST_F(DefaultEvent_test, BasicGetters) 
{
    std::string event_name { "some name" };
    pdEngine::DefaultEvent ev { pdEngine::getEventID(event_name.c_str()) };

    ASSERT_EQ(ev.getTypeID(), pdEngine::getEventID(event_name.c_str()));
}


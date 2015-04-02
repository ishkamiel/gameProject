#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events/DefaultEvent.h"

#include <cstring>

namespace pdEngineTest
{
  class DefaultEvent_test : public ::testing::Test 
  {
  protected:
  };
  
  
  TEST_F(DefaultEvent_test, BasicGetters) 
  {
    std::string event_name { "some name" };
    pdEngine::DefaultEvent ev { pdEngine::getEventID(event_name.c_str()) };
    
    ASSERT_EQ(ev.getTypeID(), pdEngine::getEventID(event_name.c_str()));
  }
}


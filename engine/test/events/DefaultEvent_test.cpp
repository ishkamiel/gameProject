#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events/DefaultEvent.h"

#include <cstring>

namespace pdEngine
{

class test_DefaultEvent : public ::testing::Test
{
protected:
};


TEST_F(test_DefaultEvent, BasicGetters)
{
  std::string event_name { "some name" };
  pdEngine::DefaultEvent ev { pdEngine::getEventID(event_name.c_str()) };

  ASSERT_EQ(ev.getTypeID(), pdEngine::getEventID(event_name.c_str()));
}

TEST_F(test_DefaultEvent, StringConstructorWorks)
{
  DefaultEvent ev_1 { "SomeEvent" };
  DefaultEvent ev_2 { "SomeEvent" };

  ASSERT_EQ(ev_1.getTypeID(), ev_2.getTypeID());
}

}


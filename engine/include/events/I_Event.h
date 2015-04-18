#pragma once

#include "events/EventTypeID.h"

#include <memory>
#include <string>

namespace pdEngine
{

class I_Event;
using Event_sptr = std::shared_ptr<I_Event>;

class I_Event
{
public:
	virtual ~I_Event() {};
    virtual const EventTypeID& getTypeID(void) const =0;
    virtual float getTimestamp(void) const =0;
};

}

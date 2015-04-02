#ifndef PDENGINE_IEVENT_H_
#define PDENGINE_IEVENT_H_

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
    virtual const EventTypeID& getTypeID(void) const =0;
    virtual float getTimestamp(void) const =0;
};

}
#endif

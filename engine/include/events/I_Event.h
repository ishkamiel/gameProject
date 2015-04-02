#ifndef PDENGINE_IEVENT_H_
#define PDENGINE_IEVENT_H_

#include "events/EventTypeID.h"

#include <memory>
#include <string>

namespace pdEngine
{

class iEvent;
using Event_sptr = std::shared_ptr<iEvent>;

class iEvent
{
public:
    virtual const EventTypeID& getTypeID(void) const =0;
    virtual float getTimestamp(void) const =0;
};

}
#endif

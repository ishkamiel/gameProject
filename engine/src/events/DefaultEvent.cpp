#include "events/DefaultEvent.h"

namespace pdEngine
{
    DefaultEvent::DefaultEvent(const EventTypeID& id)
        : typeID(id), timestamp(0)
    {}

    DefaultEvent::~DefaultEvent()
    {}

    float DefaultEvent::getTimestamp(void) const
    {
        return timestamp;
    }
}

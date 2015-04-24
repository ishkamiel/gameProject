#include "events/DefaultEvent.h"

namespace pdEngine
{
    DefaultEvent::DefaultEvent(const EventTypeID& id)
        : typeID(id), timestamp(0)
    {}

    DefaultEvent::DefaultEvent(const std::string& string)
        : DefaultEvent(getEventID(string.c_str()))
    {}

    DefaultEvent::~DefaultEvent()
    {}

    float DefaultEvent::getTimestamp(void) const noexcept
    {
        return timestamp;
    }
}

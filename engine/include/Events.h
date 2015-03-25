#ifndef PDENGINE_EVENTS_H
#define PDENGINE_EVENTS_H

#include <functional>
#include <memory>
#include <string>

namespace pdEngine
{
    using EventTypeName = std::string;
    using EventTypeID = std::size_t;

    inline EventTypeID getEventID(const EventTypeName&);
}

namespace pdEngine
{
    EventTypeID getEventID(const EventTypeName& eventName)
    {
        static std::hash<EventTypeName> hasher;
        return hasher(eventName);
    }

}

#endif /* PDENGINE_EVENTS_H */


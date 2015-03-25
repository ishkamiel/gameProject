#ifndef PDENGINE_EVENTS_H
#define PDENGINE_EVENTS_H

#include <functional>
#include <memory>
#include <string>

namespace pdEngine
{
    using EventName = std::string;
    using EventID = std::size_t;
    using EventData = std::shared_ptr<std::string>;

    using EventListener = std::function<bool(EventData)>;
    using EventListener_sptr = std::shared_ptr<EventListener>;
    using EventListener_wptr = std::weak_ptr<EventListener>;

    inline EventID getEventID(const EventName&);
}

namespace pdEngine
{
    EventID getEventID(const EventName& eventName)
    {
        static std::hash<EventName> hasher;
        return hasher(eventName);
    }
}

#endif /* PDENGINE_EVENTS_H */


#pragma once

#include "events/I_Event.h"

namespace pdEngine
{
    class DefaultEvent : public I_Event
    {
        const EventTypeID typeID;
        const float timestamp;

    public:
        DefaultEvent(void) =delete;
        DefaultEvent(const EventTypeID&);
        DefaultEvent(const std::string&);
        virtual ~DefaultEvent();

        virtual inline const EventTypeID& getTypeID(void) const noexcept override;
        virtual float getTimestamp(void) const noexcept override;
    };
}

namespace pdEngine
{
    inline const EventTypeID& DefaultEvent::getTypeID(void) const  noexcept
    {
        return typeID;
    }
}

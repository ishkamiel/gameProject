#ifndef PDENGINE_EVENTDATA_H_
#define PDENGINE_EVENTDATA_H_

#include "Events.h"

namespace pdEngine
{
    class EventData
    {
        public:
            virtual const EventTypeID& getEventTypeID(void) const =0;
            virtual const EventTypeName& getEventTypeName(void) const =0;
            virtual float getTimestamp(void) const =0;
    };

    class BaseEventData : public EventData
    {
        const EventTypeID id;
        const EventTypeName name;

        public:
        BaseEventData(void) =delete;
        BaseEventData(const EventTypeName&);

        inline const EventTypeID& getEventTypeID(void) const override final;
        inline const EventTypeName& getEventTypeName(void) const override final;
        virtual float getTimestamp(void) const override;
    };
}

namespace pdEngine
{
    inline const EventTypeID& BaseEventData::getEventTypeID(void) const 
    {
        return id;
    }

    inline const EventTypeName& BaseEventData::getEventTypeName(void) const
    {
        return name;
    }
}

#endif /* PDENGINE_EVENTDATA_H_ */

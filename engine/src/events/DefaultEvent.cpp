#include "events/DefaultEvent.h"

namespace pdEngine
{
    DefaultEvent::DefaultEvent(const EventTypeID& id)
        : typeID(id), typeName(nullptr), timestamp(0)
    {}

    DefaultEvent::~DefaultEvent()
    {}

    float DefaultEvent::getTimestamp(void) const
    {
        return timestamp;
    }

    
   // {}

    // virtual inline const EventTypeID& getTypeID(void) const override final;
    // virtual inline const EventTypeName& getTypeName(void) const override final;
    // virtual float getTimestamp(void) const override;
}

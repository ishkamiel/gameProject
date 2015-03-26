#include "EventBasic.h"

namespace pdEngine
{
    EventBasic::EventBasic(const EventTypeID& id)
        : typeID(id), typeName(nullptr), timestamp(0)
    {}

    EventBasic::~EventBasic()
    {}

    float EventBasic::getTimestamp(void) const
    {
        return timestamp;
    }

    
   // {}

    // virtual inline const EventTypeID& getTypeID(void) const override final;
    // virtual inline const EventTypeName& getTypeName(void) const override final;
    // virtual float getTimestamp(void) const override;
}

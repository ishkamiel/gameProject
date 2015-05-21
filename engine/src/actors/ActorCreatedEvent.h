#pragma once

#include "events/DefaultEvent.h"

namespace pdEngine
{
const EventTypeID VARIABLE_IS_NOT_USED ev_ActorCreated    = getEventID("ActorCreated");

class ActorCreatedEvent : DefaultEvent
{
	ActorID m_actorID;

public:
	ActorCreatedEvent(ActorID actorID)
	: DefaultEvent(ev_ActorCreated), m_actorID(actorID)
	{}

	ActorID getActorID(void) const noexcept
	{  return m_actorID; }
};

}

#pragma once

#include "actors/Actor.h"
#include "events/DefaultEvent.h"

namespace pdEngine
{
const EventTypeID ev_ActorDestoryed  = getEventID("ActorDestoyed");

class ActorDestroyedEvent : DefaultEvent
{
	ActorID m_actorID;

public:
	ActorDestroyedEvent(ActorID id)
	: DefaultEvent(ev_ActorDestroyed), m_actorID(id)
	{}

	ActorID getActorID(void) const noexcept
	{ return m_actorID; }
};

}

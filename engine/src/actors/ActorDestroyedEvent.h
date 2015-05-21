#pragma once

#include "actors/Actor.h"
#include "events/DefaultEvent.h"

namespace pdEngine
{
class ActorDestroyedEvent : public DefaultEvent
{
	ActorID m_actorID;

public:
	static constexpr EventTypeID typeID(void)
	{ return getEventID("ActorDestroyed"); }

	ActorDestroyedEvent(ActorID id)
	: DefaultEvent(typeID() ), m_actorID(id)
	{}

	ActorID getActorID(void) const noexcept
	{ return m_actorID; }
};

}

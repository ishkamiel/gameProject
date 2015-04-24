#pragma once

#include "events/EventManager.h"

namespace pdEngine
{

class ListenerHandle
{
	EventTypeID m_eventType;
	EventListener m_listener;

public:
	ListenerHandle(EventTypeID id, EventListener listener);
	virtual ~ListenerHandle();

	inline bool call(Event_sptr) const noexcept;
	inline EventTypeID getEventType(void) const noexcept;
};

/***************************************************************************************************
 * Implementations
 */

inline bool ListenerHandle::call(Event_sptr event) const noexcept
{
	return m_listener(event);
}

inline EventTypeID ListenerHandle::getEventType(void) const noexcept
{
	return m_eventType;
}

}

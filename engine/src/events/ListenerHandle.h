#pragma once

#include "events/EventManager.h"

namespace pdEngine
{

class ListenerHandle
{
	EventTypeID m_eventType;
	EventListener m_listener;

public:
	ListenerHandle(EventTypeID id, EventListener listener)
	: m_eventType(id), m_listener(listener)
	{}

	virtual ~ListenerHandle() = default;
	inline bool call(Event_sptr) const noexcept;
};

/***************************************************************************************************
 * Implementations
 */

inline bool ListenerHandle::call(Event_sptr event) const noexcept
{
	return m_listener(event);
}

}

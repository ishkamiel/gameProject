#include "events/ListenerHandle.h"

namespace pdEngine
{

ListenerHandle::ListenerHandle(EventTypeID id, EventListener listener)
: m_eventType(id), m_listener(listener) {}

ListenerHandle::~ListenerHandle()
{}

}

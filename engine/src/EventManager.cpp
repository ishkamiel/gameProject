#include "EventManager.h"

#include <iterator>
#include <map>
#include <memory>
#include <vector>

namespace pdEngine 
{
    typedef unsigned int ListenerID;

    ListenerHandle::ListenerHandle(EventID eventID, ListenerID listenerID) 
        : eventID(eventID), listenerID(listenerID) {}

    class EventManager::EventManagerImpl 
    {
        typedef std::map<ListenerID, EventListener> ListenerMap;
        typedef std::map<EventID, ListenerMap> EventMap;

        public:
            EventManagerImpl();
            ~EventManagerImpl();
            inline ListenerHandlePtrS addListener(EventID, EventListener);
            inline void removeListener(ListenerHandlePtrS);
            inline void fireEvent(EventID, EventData);
        private:
            std::unique_ptr<EventMap> eventListeners;
    };
}

namespace pdEngine
{
    EventManagerPtrS EventManager::getEventManager()
    {
        static EventManagerPtrS em {};
        return em;
    }
}

namespace pdEngine
{
    EventManager::EventManager() : impl( new EventManagerImpl)
    {}

    ListenerHandlePtrS 
        EventManager::addListener(EventID id, EventListener listener)
    {
        return impl->addListener(id, listener);
    }

    void EventManager::removeListener(
            ListenerHandlePtrS listenerHandle) 
    {
        impl->removeListener(listenerHandle);
    }

    void EventManager::fireEvent(EventID id, EventData data)
    {
        impl->fireEvent(id, data);
    }
}

namespace pdEngine
{
    EventManager::EventManagerImpl::EventManagerImpl() 
        : eventListeners(new EventMap)
    {}

    ListenerHandlePtrS
        EventManager::EventManagerImpl::addListener
        (EventID eventID, EventListener listener)
    {
        static ListenerID listenerID {0};
        
        eventListeners->operator[](eventID).operator[](listenerID) = listener;

        ListenerHandlePtrS retval {
            new ListenerHandle(eventID, listenerID)
        };

        ++listenerID;

        return retval;
    }

    void EventManager::EventManagerImpl::removeListener
        (ListenerHandlePtrS listener)
    {
        EventMap::iterator it = eventListeners->find(listener->getEventID());

        if (it != eventListeners->end())
        {
            it->second.erase(listener->getListenerID());
        }
    }

    void EventManager::EventManagerImpl::fireEvent
        (EventID id, EventData data)
    {
        EventMap::iterator event = eventListeners->find(id);

        if (event != eventListeners->end())
            for (auto l : event->second)
                l.second(data);
    }
}



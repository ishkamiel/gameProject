#include "EventManager.h"
#include <vector>
#include <memory>
#include <list>
#include <map>

namespace pdEngine 
{
    typedef std::shared_ptr<EventManager::ListenerHandleImpl> SharedHandlePtr;

    class EventManager::EventManagerImpl 
    {
        typedef std::list<EventListener> ListenerList;
        typedef std::map<EventID, ListenerList> ListenerMap;

        public:
            EventManagerImpl();
            ~EventManagerImpl();
            inline ListenerHandle addListener(EventID, EventListener);
            inline void removeListener(EventID, ListenerHandle);
            inline void fireEvent(EventID, EventData);
        private:
            std::unique_ptr<ListenerMap> listenerMap;
    };

    class EventManager::ListenerHandleImpl
    {
        public:
            ListenerHandleImpl(EventListener);
            ~ListenerHandleImpl();
    };
}

namespace pdEngine
{
    EventManagerPtr getEventManager()
    {
        static EventManagerPtr em {};
        return em;
    }
}

namespace pdEngine
{
    EventManager::EventManager() : impl( new EventManagerImpl)
    {}

    EventManager::ListenerHandle 
        EventManager::addListener(EventID id, EventListener listener)
    {
        return impl->addListener(id, listener);
    }

    void EventManager::removeListener(EventID id, ListenerHandle listenerHandle) 
    {
        impl->removeListener(id, listenerHandle);
    }

    void EventManager::fireEvent(EventID id, EventData data)
    {
        impl->fireEvent(id, data);
    }
}

namespace pdEngine
{
    EventManager::EventManagerImpl::EventManagerImpl() 
        : listenerMap(new ListenerMap)
    {}

    EventManager::ListenerHandle
        EventManager::EventManagerImpl::addListener
        (EventManager::EventID id, EventManager::EventListener listener)
    {
        SharedHandlePtr ptr { new EventManager::ListenerHandleImpl(listener) };
        listenerMap->operator[](id).push_back(listener);
        return ptr;
    }

    void EventManager::EventManagerImpl::removeListener
        (EventID id, ListenerHandle listener)
    {
        // TODO
        void(id), void(listener);
    }

    void EventManager::EventManagerImpl::fireEvent
        (EventID id, EventData data)
    {
         auto search = listenerMap->find(id);
         if(search != listenerMap->end()) {
             for (auto l : search->second)
                 l(data);
         }
    }
}



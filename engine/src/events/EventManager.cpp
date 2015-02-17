#include "EventManager.h"
#include <vector>
#include <memory>
#include <list>
#include <map>

namespace pdEngine 
{
    class EventManagerImpl 
    {
        typedef std::list<EventListener> ListenerList;
        typedef std::map<EventID, ListenerList> ListenerMap;

        public:
            EventManagerImpl();
            ~EventManagerImpl();
            inline EventListenerPtrW addListener(EventID, EventListener);
            inline void removeListener(EventID, EventListenerPtrW);
            inline void fireEvent(EventID, EventData);
        private:
            std::unique_ptr<ListenerMap> listenerMap;
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

    EventListenerPtrW EventManager::addListener(EventID id, EventListener listener)
    {
        return impl->addListener(id, listener);
    }

    void EventManager::removeListener(EventID id, EventListenerPtrW listener) 
    {
        impl->removeListener(id, listener);
    }

    void EventManager::fireEvent(EventID id, EventData data)
    {
        impl->fireEvent(id, data);
    }
}

namespace pdEngine
{
    EventManagerImpl::EventManagerImpl() : listenerMap(new ListenerMap)
    {}

    EventListenerPtrW EventManagerImpl::addListener(EventID id, EventListener listener)
    {
        EventListenerPtrS ptr { new EventListenerHandle(listener) };
        listenerMap->operator[](id).push_back(listener);
        EventListenerPtrW retval { ptr };
        return (retval);
    }

    void EventManagerImpl::removeListener(EventID id, EventListenerPtrW listener)
    {
        return true;
    }

    void EventManagerImpl::fireEvent(EventID id, EventData data)
    {
         auto search = listenerMap->find(id);
         if(search != listenerMap->end()) {
             for (auto l : search->second)
                 l(data);
         }
    }
}



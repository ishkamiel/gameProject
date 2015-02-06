#include "EventManager.h"
#include <vector>
#include <memory>

namespace pdGame 
{
    class EventManagerImpl;

    std::shared_ptr<EventManager> em = nullptr;

    std::shared_ptr<EventManager> getEventManager()
    {
        if (em != nullptr) return em;

        std::shared_ptr<EventManager> em {};
        return em;
    }

    class EventManagerImpl 
    {
        public:
            EventManagerImpl();
            ~EventManagerImpl();
            bool addListener(std::string event_name, std::function<void()> listener);
            bool removeListener(std::string event_name, std::function<void()> listener);
            void fireEvent(std::string event_name);
    };

    EventManager::EventManager() : impl( new EventManagerImpl)
    {}

    bool EventManager::addListener(std::string event_name, std::function<void()> listener)
    {
        return impl->addListener(event_name, listener);
    }

    bool EventManager::removeListener(std::string event_name, std::function<void()> listener) 
    {
        return impl->removeListener(event_name, listener);
    }

    void EventManager::fireEvent(std::string event_name) 
    {
        impl->fireEvent(event_name);
    }

    EventManagerImpl::EventManagerImpl() {}

    bool EventManagerImpl::addListener(std::string event_name, std::function<void()> listener)
    {
        return true;
    }

    bool EventManagerImpl::removeListener(std::string event_name, std::function<void()> listener) 
    {
        return true;
    }

    void EventManagerImpl::fireEvent(std::string event_name) 
    {
    }
}



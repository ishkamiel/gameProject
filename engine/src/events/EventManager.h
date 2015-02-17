#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <memory>
#include <string>
#include <functional>

namespace pdEngine
{
    class EventManager;
    typedef std::shared_ptr<EventManager> EventManagerPtr;

    std::shared_ptr<EventManager> getEventManager();

    class EventManager
    {
        public:
            class ListenerHandleImpl;
            class EventManagerImpl;
            
            typedef std::string EventData;
            typedef unsigned int EventID;
            typedef std::function<void(EventData)> EventListener;
            typedef std::weak_ptr<ListenerHandleImpl> ListenerHandle;

            ListenerHandle addListener(EventID, EventListener);
            void removeListener(EventID, ListenerHandle);
            void fireEvent(EventID, EventData);

        private:
            std::unique_ptr<EventManagerImpl> impl;
            EventManager();
            ~EventManager();
    };
}

#endif


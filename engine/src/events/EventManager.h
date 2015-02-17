#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <memory>
#include <string>
#include <functional>

namespace pdEngine
{
    class EventManager;
    class EventManagerImpl;
    class EventListenerHandle;

    typedef std::string EventData;
    typedef std::shared_ptr<EventManager> EventManagerPtr;
    typedef std::function<void(EventData)> EventListener;
    typedef int EventID;
    typedef int ListenerID;
    typedef std::shared_ptr<EventListenerHandle> EventListenerPtrS;
    typedef std::weak_ptr<EventListenerHandle> EventListenerPtrW;

    EventManagerPtr getEventManager();


    class EventManager
    {
        class EventListenerHandle
        {
            public:
                ~EventListenerHandle();
                void cancel();
            private:
                EventListenerHandle(EventListener);
                inline void fire();
                inline ListenerID listenerID();
                inline EventID eventID();
                inline bool isRemoved();
        };

        public:
            EventListenerPtrW addListener(EventID, EventListener);
            void removeListener(EventID, EventListenerPtrW);
            void fireEvent(EventID, EventData);

        private:
            std::unique_ptr<EventManagerImpl> impl;
            EventManager();
            ~EventManager();
    };
}

#endif


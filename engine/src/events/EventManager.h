#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <memory>
#include <string>
#include <functional>

namespace pdEngine
{
    class ListenerHandle;
    class EventManager;

    typedef std::string EventData;
    typedef unsigned int EventID;
    typedef unsigned int ListenerID;
    typedef std::shared_ptr<ListenerHandle> ListenerHandlePtrS;
    typedef std::shared_ptr<EventManager> EventManagerPtrS;
    typedef std::function<void(EventData)> EventListener;

    class ListenerHandle
    {
        friend class EventManager;

        EventID eventID;
        ListenerID listenerID;

        public:
            ~ListenerHandle() {};
            inline EventID getEventID() { return eventID; };
            inline ListenerID getListenerID() { return listenerID; }
        private: 
            ListenerHandle(EventID, ListenerID);
    };

    class EventManager
    {
        class EventManagerImpl;
        std::unique_ptr<EventManagerImpl> impl;

        public:
            static EventManagerPtrS getEventManager();

            ListenerHandlePtrS addListener(EventID, EventListener);
            void removeListener(ListenerHandlePtrS);
            void removeEvent(EventID);
            void fireEvent(EventID, EventData);

        private:
            EventManager();
            ~EventManager();
    };
}

#endif


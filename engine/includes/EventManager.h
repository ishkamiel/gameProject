#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "General.h"
#include "Task.h"

#include <memory>
#include <string>
#include <functional>
#include <vector>

namespace pdEngine
{
    class EventListener;
    class EventManager;

    typedef std::string EventData;
    typedef std::function<void(EventData)> EventListenerDelegate;
    typedef std::vector<EventID> EventList;
    typedef std::shared_ptr<EventManager> EventManagerSharedPtr;


    class EventListener
    {
    public:
    	EventListener(EventID, EventListenerDelegate);
    	EventListener(EventList, EventListenerDelegate);
    	~EventListener();

    	EventList getEventList() const;
    	void cancelAll();
    	void canel(EventID);
    private:
    };

    class EventManager : public Task
    {
        class EventManagerImpl;

        friend EventManagerSharedPtr getEventManager();
    	friend class EventListener;
    	friend class EventListenerImpl;

        public:
            void fireEvent(EventID, EventData);

        private:
            EventManager();
            ~EventManager();

            void addListener(const EventID, const EventListenerDelegate&);
            void removeListener(const EventID, const EventListenerDelegate&);

	        std::unique_ptr<EventManagerImpl> impl;
    };

    EventManagerSharedPtr getEventManager();
}

#endif


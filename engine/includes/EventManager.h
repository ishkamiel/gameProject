#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "General.h"
#include "Task.h"

#include <memory>
#include <string>
#include <functional>

namespace pdEngine
{
    class EventListener;
    class EventManager;

    typedef std::function<void(EventData)> EventListenerDelegate;
    typedef std::vector<EventID> EventList;
    typedef std::string EventData;

    static EventManager& getEventManager();

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

    class EventManager : public ITask
    {
        class EventManagerImpl;

    	friend class EventListener;
    	friend class EventListenerImpl;
        friend EventManager& getEventManager();

        public:
            void fireEvent(EventID, EventData);

        private:
            EventManager();
            ~EventManager();

            void addListener(const EventID, const EventListenerDelegate&);
            void removeListener(const EventID, const EventListenerDelegate&);

	        std::unique_ptr<EventManagerImpl> impl;
    };
}

#endif


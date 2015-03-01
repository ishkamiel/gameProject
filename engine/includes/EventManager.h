#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "General.h"
#include "Task.h"

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace pdEngine
{
	class EventListener;
	class EventManager;
	
	typedef std::shared_ptr<std::string>      EventData;
	typedef std::function<bool(EventData)>    ListenerFunction;
	typedef std::shared_ptr<ListenerFunction> ListenerFunction_sptr;
	typedef std::weak_ptr<ListenerFunction>   ListenerFunction_wptr;
	typedef std::unique_ptr<EventListener> 	  EventListener_uptr;
    typedef std::shared_ptr<EventManager>     EventManager_sptr;

	class EventListener
	{
		friend class EventManager;

		EventManager*           eventManager;
		EventID                 eventID;
		ListenerFunction_wptr   listenerFunction;

	public:
		EventID getEventID() const;
		void cancel();
		~EventListener();

	private:
		EventListener();
		EventListener(EventManager*, const EventID, ListenerFunction_wptr);
	};
	
    class EventManager : public Task
    {
        friend class EventListener;

        struct PendingEvent
        {
            EventID   id;
            EventData data;
        };
            
        typedef std::vector<ListenerFunction_sptr> 	DelegateVector;
        typedef std::map<EventID, DelegateVector> 	EventListenerMap;
        typedef std::queue<PendingEvent> 			EventQueue;

        EventListenerMap    eventListeners  {};
        EventQueue          eventQueueIn    {};
        EventQueue          eventQueueOut   {};

    public:
        EventManager();
        ~EventManager();

        void fireEvent(EventID, EventData);
        void onUpdate(TimeDelta) override;
        EventListener_uptr createListener(const EventID, ListenerFunction);

    private:
        void addListener(const EventID, ListenerFunction);
        void removeListener(const EventID, ListenerFunction_sptr);
    };
}

#endif


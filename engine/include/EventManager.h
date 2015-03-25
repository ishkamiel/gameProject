#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "Events.h"
#include "EventListener.h"
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
	class EventManager;
    using EventManager_sptr = std::shared_ptr<EventManager>;
	
    class EventManager : public Task
    {
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

        void onUpdate(TimeDelta) override;

        int fireEvent(const EventID&, EventData);
        int fireEvent(const EventName&, EventData);

        EventListener addListener(const EventName&, ListenerFunction);
        EventListener addListener(const EventID, ListenerFunction);
        bool removeListener(const EventID, ListenerFunction_sptr);

    private:
    };
}

#endif


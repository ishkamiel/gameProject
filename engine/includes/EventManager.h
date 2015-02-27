#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "General.h"
#include "Task.h"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace pdEngine
{
	class EventListener;
	class EventManager;
	
	typedef std::string EventData;
	typedef std::function<bool(EventData)> EventListenerDelegate;
	typedef std::vector<EventID> EventList;
	typedef std::shared_ptr<EventManager> EventManagerSharedPtr;
	typedef std::unique_ptr<EventListener> EventListenerUniquePtr;
	
	
	class EventListener
	{
		friend class EventManager;

	public:
		EventList getEventList() const;
		void cancelAll();
		void canel(EventID);

	private:
		EventListener(EventID, EventListenerDelegate);
		EventListener(EventList, EventListenerDelegate);
		~EventListener();
	};
	
	class EventManager : public Task
	{
		friend EventManagerSharedPtr getEventManager();
		friend class EventListener;

		typedef std::shared_ptr<std::vector<EventListenerDelegate>> EventListenerList;
		typedef std::map<EventID, EventListenerList> EventMap;

		EventMap eventListeners;
		
	public:
		EventManager();
		~EventManager();

		int fireEvent(EventID, EventData);
		EventListenerUniquePtr createEventListener(EventID, EventListenerDelegate);
		EventListenerUniquePtr createEventListener(EventList, EventListenerDelegate);
		
	private:
		void addListener(const EventID, const EventListenerDelegate&);
		void removeListener(const EventID, const EventListenerDelegate&);
	};
}

#endif


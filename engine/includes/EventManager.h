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
	typedef std::shared_ptr<EventManager> EventManagerSharedPtr;
	typedef std::unique_ptr<EventListener> EventListenerUniquePtr;

	class EventListener
	{
		friend class EventManage;

		EventID eventID;
		EventListenerDelegate& delegate;
		EventManagerSharedPtr eventManager;

	public:
		const EventID getEventID() const;
		void cancel();

	private:
		EventListener();
		EventListener(EventManagerSharedPtr, const EventID, EventListenerDelegate&);
		~EventListener();
	};
	
	class EventManager : public Task
	{
		friend class EventListener;

		typedef std::shared_ptr<std::vector<EventListenerDelegate>> EventListenerList;
		typedef std::map<EventID, EventListenerList> EventMap;

		EventMap eventListeners;
		
	public:
		EventManager();
		~EventManager();

		int fireEvent(const EventID, const EventData&);
		EventListenerUniquePtr createEventListener(const EventID, EventListenerDelegate&);
		
	private:
		void addListener(const EventID, const EventListenerDelegate&);
		void removeListener(const EventID, const EventListenerDelegate&);
	};
}

#endif


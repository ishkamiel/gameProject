#include "events/EventManagerImpl.h"

#include "events/I_Event.h"
#include "events/DefaultEvent.h"
#include "events/ListenerHandle.h"
#include "utils/Logger.h"

#include <cassert>
#include <algorithm>
#include <memory>

namespace pdEngine
{
    EventManagerImpl::EventManagerImpl()
    {}

    EventManagerImpl::~EventManagerImpl()
    {
        //TODO Do we need to clean something up?
    }


    void EventManagerImpl::onUpdate(int deltaMs) noexcept
    {
        (void)deltaMs;

        if (eventQueueIn.size() == 0) return;

        PDE_DEBUG << "EventManager processing queued events";

        std::swap(eventQueueIn, eventsProcessing);

        while (eventsProcessing.size() > 0) {
            auto event = eventsProcessing.front();
            eventsProcessing.pop();

            assert(event);
            PDE_DEBUG << "Processing event of type " << event->getTypeID();

            auto listenersCalled = 0;

            auto found = eventMap.find(event->getTypeID());

            if (found != eventMap.end()) {
                auto list = found->second;

                PDE_DEBUG << "Found " << list.size() << " listeners";

                for (auto i : list) {
                    if (auto listener = i.lock()) {
                        PDE_DEBUG << "Calling listener";
                        listener->call(event);
                        ++listenersCalled;
                    }
                    else {
                        // TODO: probably shouldn't be here, unless multithreading?
                        assert(false);
                    }
                }
            }

            PDE_DEBUG << "Event processed by " << listenersCalled << " listeners";
        }
    }

    void EventManagerImpl::queueEvent(const EventTypeID id) noexcept
    {
        eventQueueIn.push(std::make_shared<DefaultEvent>(id));
    }

    void EventManagerImpl::queueEvent(const Event_sptr eventPtr) noexcept
    {
        PDE_DEBUG << "Queing new event EventTypeID: " << eventPtr->getTypeID();
        eventQueueIn.push(eventPtr);
    }

    /*
    void EventManager::addListener( const EventTypeName eventName, EventListener listener)
    {
        addListener(getEventID(eventName), listener);
    }
    */

    ListenerHandle_sptr EventManagerImpl::addListener(
            const EventTypeID& eventID, EventListener listener) noexcept
    {
        // TODO FIXME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        auto handle_ptr = std::shared_ptr<ListenerHandle>(
            new ListenerHandle(eventID, listener),
            [=](ListenerHandle*) {
                // TODO do the cleanup here!
            });

        auto found = eventMap.find(eventID);

        if (found == eventMap.end()) {
            /**
             * If no list was found, create one with emplace which conveniently
             * returns iterator to newly created pair.
             */
            auto pair = eventMap.emplace(std::make_pair(eventID, ListenerList()));
            assert(pair.second == true); // true if insertion happened
            found = pair.first;
        }

        auto listeners = found->second;

        listeners.push_back(handle_ptr);

        //assert(list->size() != 0);
        //assert(list->size() == eventMap[eventID]->size());

        PDE_DEBUG << "Added listener for event, EventTypeID << " << eventID;
        return handle_ptr;
    }

/*
	ListenerList* EventManagerImpl::findEventList(EventTypeID id, bool create)
    {
        auto f = eventMap.find(id);
        if (f == eventMap.end()) 
        {
            if (create)
            {
                eventMap.insert(EventMapPair(id, new ListenerList()));
                return findEventList(id);
            }
            return nullptr;
        }

        return f->second;
    }
    */
}

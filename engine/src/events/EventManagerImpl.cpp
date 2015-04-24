#include "events/EventManagerImpl.h"

#include "events/I_Event.h"
#include "events/DefaultEvent.h"
#include "events/ListenerHandle.h"
#include "utils/Logger.h"
#include "utils/Memory.h"

#include <cassert>
#include <algorithm>
#include <memory>

namespace pdEngine
{

EventManagerImpl::EventManagerImpl()
{}

EventManagerImpl::~EventManagerImpl()
{
    for (auto pair : eventMap) {
        safeDelete(pair.second);
        pair.second = nullptr;
    }
}


void EventManagerImpl::onUpdate(int deltaMs) noexcept
{
    (void) deltaMs; // ignore

    /*
     * Remove expired listener weak pointers.
     * Set ensures lists are iterated only once. Needs to be done separately from event
     * processing since event processing might actually cause expiration of listeners.
     */
    while (!m_cleanupList.empty()) {
        auto iter = m_cleanupList.begin();

        auto f = eventMap.find(*iter);
        if (f != eventMap.end()) {
            auto list = f->second;
            list->erase(std::remove_if(list->begin(),
                                       list->end(),
                                       [](auto p) { return p.expired(); }),
                        list->end());

            if (list->empty()) {
                // FIXME: Not thread safe, addListener might be accessing at same time!
                safeDelete(f->second);
                f->second = nullptr;
                eventMap.erase(f);
            }
        }

        m_cleanupList.erase(iter);
    }

    /*
     * Process events
     */
    if (eventQueueIn.size() != 0) {
        PDE_DEBUG << "EventManager processing queued events";

        /*
         * Keep separate processing and in queues to make sure that events procuding more events
         * don't end up in a endless loop.
         */
        std::swap(eventQueueIn, eventsProcessing);

        while (eventsProcessing.size() > 0) {
            auto event = eventsProcessing.front();
            eventsProcessing.pop();

            PDE_TRACE << "Processing event of type " << event->getTypeID();

            auto found = eventMap.find(event->getTypeID());
            if (found != eventMap.end()) {
                auto list = found->second;
                PDE_TRACE << "Found " << list->size() << " listeners";
                p_processEvent(list, event);
            }
        }
    }
}

void EventManagerImpl::p_processEvent(
    const ListenerList* list, const Event_sptr event) const noexcept
{
    for (auto i : *list) {
        if (auto listener = i.lock()) {
            PDE_TRACE << "Calling listener";
            if (!listener->call(event)) {
                return;
            }
        }
        else {
            /*
			 * Since processed events could trigger ListenerHandle destruction some
			 * listeners might get expired during this loop, and therefore end up here.
			 * Logging this to get some indication of missed cleanup.
			 */
            PDE_DEBUG << "Encountered dead ListenerHandle in onUpdate";
        }
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

ListenerHandle_sptr EventManagerImpl::addListener(
    const EventTypeID& eventID, EventListener listener) noexcept
{
    auto found = eventMap.find(eventID);

    if (found == eventMap.end()) {
        PDE_TRACE << "Creating new ListenerList for event type " << eventID;
        /**
		 * If no list was found, create one with emplace which conveniently
		 * returns iterator to newly created pair.
		 */
        auto pair = eventMap.emplace(std::make_pair(eventID, new ListenerList()));
        assert(pair.second == true); // true if insertion happened
        found = pair.first;

        // Make sure this trickery worked!
        assert(eventMap.find(eventID) != eventMap.end());
    }

    auto listPointer = found->second;

    auto handle_ptr = std::shared_ptr<ListenerHandle>(
        new ListenerHandle(eventID, listener),
        [=](ListenerHandle* rawPointer) {
            PDE_TRACE << "Cleaning up event listener for event of type "
                      << rawPointer->getEventType();
            m_cleanupList.insert(rawPointer->getEventType());
            delete rawPointer;
        });

    listPointer->push_back(handle_ptr);
    assert(listPointer->size() != 0);

    PDE_DEBUG << "Added listener for event of type " << eventID;
    return handle_ptr;
}

}

/* 
 * File:   I_EventManager.h
 * Author: ishkamiel
 *
 * Created on April 2, 2015, 10:47 PM
 */

#ifndef I_EVENTMANAGER_H
#define	I_EVENTMANAGER_H

#include "events/EventListener.h"

namespace pdEngine {

class EventManager;
using EventManager_sptr = std::shared_ptr<EventManager>;

class EventManager {
public:
	virtual ~EventManager() {}

    virtual void queueEvent(const Event_sptr) = 0;
    virtual void queueEvent(const EventTypeID) = 0;
    virtual void addListener(const EventTypeID, EventListener) = 0;

    static EventManager_sptr getSingleton();
};


}

#endif	/* I_EVENTMANAGER_H */


#include "events/EventManager.h"
#include "events/EventManagerImpl.h"

#include <memory>

namespace pdEngine {

EventManager_sptr EventManager::getSingleton() {
	static std::shared_ptr<EventManager> instance = std::make_shared<EventManagerImpl>();
	return instance;
}

}
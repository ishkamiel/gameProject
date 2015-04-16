#pragma once

#include "events/EventManager.h"
#include "resources/ResourceManager.h"

#include <memory>

namespace pdEngine
{

class Root
{
public:
	Root();
	virtual ~Root();

	void setEventManager(std::shared_ptr<EventManager>) noexcept;
	void setResourceManager(std::shared_ptr<ResourceManager>) noexcept;
	std::shared_ptr<EventManager> getEventManager() const noexcept;
	std::shared_ptr<ResourceManager> getResourceManager() const noexcept;
private:

	std::shared_ptr<EventManager> m_EventManager;
	std::shared_ptr<ResourceManager> m_ResourceManager;
};

std::shared_ptr<Root> getRoot(void) noexcept;


}

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

	inline EventManager_sptr getEventManager() const noexcept { return m_EM; };
	inline ResourceManager_sptr getResourceManager() const noexcept { return m_RM; };

	void setEventManager(EventManager_sptr) noexcept;
	void setResourceManager(ResourceManager_sptr) noexcept;
private:
	EventManager_sptr m_EM;
	ResourceManager_sptr m_RM;
};

std::shared_ptr<Root> getRoot(void) noexcept;

}

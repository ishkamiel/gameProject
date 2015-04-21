#pragma once

#include <memory>

namespace pdEngine
{

class EventManager;
class ResourceManager;

class Root
{
	std::shared_ptr<EventManager> m_eventManager;
	std::shared_ptr<ResourceManager>  m_resourceManager;

public:
	static std::shared_ptr<Root> get() noexcept;

	std::shared_ptr<EventManager> getEventManager() const noexcept;
	std::shared_ptr<ResourceManager> getResourceManager() const noexcept;

	void setEventManager(std::shared_ptr<EventManager>) noexcept;
	void setResourceManager(std::shared_ptr<ResourceManager>) noexcept;
private:
	Root();
	virtual ~Root();
};

inline std::shared_ptr<Root> getRoot() noexcept
{
	return Root::get();
}

}

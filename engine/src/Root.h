#pragma once

#include "utils/Deprecated.h"

#include <cassert>
#include <memory>

namespace pdEngine
{

class EventManager;
class ResourceManager;
class Logger;

/*
 * Used for engine wide global access to various core components.
 */
class Root
{
	std::shared_ptr<EventManager> m_eventManager;
	std::shared_ptr<ResourceManager>  m_resourceManager;

public:
	virtual ~Root();

	DEPRECATED(static std::shared_ptr<Root> get() noexcept);

	std::shared_ptr<EventManager> getEventManager() const noexcept;
	std::shared_ptr<ResourceManager> getResourceManager() const noexcept;

	void setEventManager(std::shared_ptr<EventManager>) noexcept;
	void setResourceManager(std::shared_ptr<ResourceManager>) noexcept;

	/**
	 * @brief Resets all shared pointers.
	 */
	void reset(void) noexcept;

	/**
	 * @brief Checks that all shared pointers point to some object.
	 *
	 * @return false if any pointer is a nullptr, otherwise true.
	 */
	bool isAllSet(void) noexcept;
private:
	Root();
};

DEPRECATED(inline std::shared_ptr<Root> getRoot() noexcept);

/***************************************************************************************************
 * Definitions
 */

inline std::shared_ptr<Root> getRoot() noexcept
{
	return Root::get();
}

inline std::shared_ptr<EventManager> Root::getEventManager() const noexcept
{
	assert(m_eventManager);
	return m_eventManager;
}

inline std::shared_ptr<ResourceManager> Root::getResourceManager() const noexcept
{
	assert(m_resourceManager);
	return m_resourceManager;
}

}

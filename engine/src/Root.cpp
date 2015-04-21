#include "Root.h"

#include <cassert>

namespace pdEngine
{

Root::Root() = default;
Root::~Root() = default;

std::shared_ptr<Root> Root::get(void) noexcept
{
	static std::shared_ptr<Root> root {};
	return root;
}

std::shared_ptr<EventManager> Root::getEventManager() const noexcept
{
	assert(m_eventManager);
	return m_eventManager;
}

std::shared_ptr<ResourceManager> Root::getResourceManager() const noexcept
{
	assert(m_resourceManager);
	return m_resourceManager;
}

void Root::setEventManager(std::shared_ptr<EventManager> em) noexcept
{
	assert(em);
	m_eventManager = em;
}

void Root::setResourceManager(std::shared_ptr<ResourceManager> rm) noexcept
{
	assert(rm);
	m_resourceManager = rm;
}

}

#include "Root.h"

#include <cassert>

namespace pdEngine
{

std::shared_ptr<Root> getRoot(void) noexcept
{
	static std::shared_ptr<Root> theRoot = std::make_shared<Root>();

	return theRoot;
}

Root::Root() = default;
Root::~Root() = default;

void Root::setEventManager(std::shared_ptr<EventManager> em) noexcept {
	assert(!m_EventManager);
	m_EventManager = em;
}

void Root::setResourceManager(std::shared_ptr<ResourceManager> rm) noexcept {
	assert(!m_ResourceManager);
	m_ResourceManager = rm;
}

std::shared_ptr<EventManager> Root::getEventManager() const noexcept {
	return m_EventManager;
}

std::shared_ptr<ResourceManager> Root::getResourceManager() const noexcept {
	return m_ResourceManager;
}

}

#include "Root.h"

#include <cassert>

namespace pdEngine
{

Root::Root()
{}

Root::~Root() = default;

std::shared_ptr<Root> Root::get(void) noexcept
{
	static std::shared_ptr<Root> root = std::shared_ptr<Root> (new Root());
	return root;
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

void Root::reset(void) noexcept
{
	m_resourceManager.reset();
	m_eventManager.reset();
}

bool Root::isAllSet(void) noexcept
{
	if (!m_eventManager) return false;
	if (!m_resourceManager) return false;
	return true;
}



}

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

void Root::setLogger(std::shared_ptr<Logger> l) noexcept
{
	assert(l);
	m_Logger = l;
}

void Root::reset(void) noexcept
{
	m_Logger.reset();
	m_resourceManager.reset();
	m_eventManager.reset();
}

bool Root::isAllSet(void) noexcept
{
	if (!m_Logger) return false;
	if (!m_eventManager) return false;
	if (!m_resourceManager) return false;
	return true;
}



}

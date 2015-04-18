#include "Root.h"

namespace pdEngine
{

Root::Root() = default;
Root::~Root() = default;

void Root::setEventManager(EventManager_sptr em) noexcept
{
	m_EM = em;
}

void Root::setResourceManager(ResourceManager_sptr rm) noexcept
{
	m_RM = rm;
}

}

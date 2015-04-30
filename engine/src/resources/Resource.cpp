#include "resources/Resource.h"

#include <algorithm>

namespace pdEngine
{
Resource::Resource(const std::string &n)
	: m_name(n)
{
	std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
}

Resource::~Resource()
{ }
}

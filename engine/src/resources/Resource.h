#pragma once

#include <string>

namespace pdEngine
{
class Resource
{
public:
	std::string m_name;

public:
	Resource(const std::string &name);
	~Resource();

	const std::string getContainerName(void) const noexcept;

	inline const std::string &getName(void) const noexcept
	{ return m_name; }
};
}

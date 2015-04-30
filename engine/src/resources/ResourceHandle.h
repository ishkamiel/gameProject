#pragma once

#include "resources/Resource.h"

#include <memory>

namespace pdEngine
{

class ResourceHandle
{
	std::shared_ptr<Resource> m_resource;
	char *buffer;
	unsigned int size;
	// iResourceExtraData_sptr extra;

public:
	ResourceHandle(std::shared_ptr<Resource>, char *, unsigned int);
	virtual ~ResourceHandle();

	unsigned int getSize(void) const noexcept;
	const char *getBuffer(void) const noexcept;
	char *getWritableBuffer(void) noexcept;
	const std::string &getName(void) const noexcept;

	// iResourceExtraData_sptr getExtra();
	// void setExtra(iResourceExtraData_sptr);

protected:
private:

};

using ResourceHandle_sptr = std::shared_ptr<ResourceHandle>;
}

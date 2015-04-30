#pragma once

#include "I_ResourceContainer.h"

#include <boost/filesystem.hpp>

#include <list>

namespace pdEngine
{

namespace fs = boost::filesystem;

class DirectoryContainer : public I_ResourceContainer
{
	fs::path m_Path;
	std::list<std::pair<std::string, size_t>> m_Resources;

public:
	DirectoryContainer(const std::string &path);
	virtual ~DirectoryContainer();

	virtual std::string v_getName(void) const noexcept;

	virtual bool v_open(void) override;
	virtual int v_getResourceCount(void) const override;
	virtual std::string v_getResourceName(int) const override;
	virtual int v_getRawResourceSize(std::shared_ptr<Resource>) override;
	virtual int v_loadRawResource(std::shared_ptr<Resource>, char *) override;
};

}

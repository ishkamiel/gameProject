#pragma once

#include "I_ResourceContainer.h"

#include <boost/filesystem.hpp>
#include <map>

namespace pdEngine
{

namespace fs = boost::filesystem;

class DirectoryContainer : public I_ResourceContainer
{
	using ResourceEntry = std::pair<fs::path, size_t>;

	fs::path m_Path;
	std::string m_name;
	std::map<std::string, ResourceEntry> m_Resources;

public:
	DirectoryContainer(const std::string &path);
	virtual ~DirectoryContainer();

	virtual std::string v_getName(void) const noexcept;

	virtual bool v_open(void) noexcept override;
	virtual int v_getResourceCount(void) const noexcept override;
	virtual std::string v_getResourceName(int) const noexcept override;
	virtual int v_getRawResourceSize(Resource *) noexcept override;
	virtual int v_loadRawResource(Resource *, char *) noexcept override;

private:
	bool readDirectory(fs::path dir) noexcept;
};

}

#include "resources/DirectoryContainer.h"
#include "utils/Logger.h"

namespace pdEngine
{

DirectoryContainer::DirectoryContainer(const std::string &path)
: m_Path(path)
{}

DirectoryContainer::~DirectoryContainer()
{ }

std::string DirectoryContainer::v_getName(void) const noexcept
{
	return m_Path.string();
}

int DirectoryContainer::v_getResourceCount(void) const
{
	return 0;
}

bool DirectoryContainer::v_open(void)
{
	if (!fs::exists(m_Path)) {
		PDE_ERROR << "Cannot find '"  << m_Path.string() << "'";
		return false;
	}

	if (!fs::is_directory(m_Path)) {
		PDE_ERROR << "Not a directory: '" << m_Path.string() << "'";
		return false;
	}

	try {
		//readDirectory(m_Path);
	}
	catch (const std::exception e) {
		PDE_ERROR << "Error while reading " << m_Path.string() << "': " << e.what();
		return false;
	}

	return false;
}

std::string DirectoryContainer::v_getResourceName(int i) const
{
	(void) i;
	throw std::out_of_range("Unknown resource");
}

int DirectoryContainer::v_getRawResourceSize(std::shared_ptr<Resource> r)
{
	(void) r;
	throw std::out_of_range("Unknown resource");
}

int DirectoryContainer::v_loadRawResource(std::shared_ptr<Resource> r, char *buffer)
{
	(void) r;
	(void) buffer;
	throw std::out_of_range("Unknown resource");
}

} /* namespace pdEngine */

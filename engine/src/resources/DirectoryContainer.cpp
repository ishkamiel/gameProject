#include "resources/DirectoryContainer.h"
#include "utils/Logger.h"
#include "utils/Memory.h"

#include <climits>
#include <fstream>
#include <memory>
#include <vector>

namespace pdEngine
{

DirectoryContainer::DirectoryContainer(const std::string &path)
: m_Path(path)
{
	auto parent = m_Path.parent_path().string();
	m_name = m_Path.string();
	m_name.erase(0, parent.length() + 1);
}

DirectoryContainer::~DirectoryContainer()
{ }

std::string DirectoryContainer::v_getName(void) const noexcept
{
	return m_name;
}

int DirectoryContainer::v_getResourceCount(void) const noexcept
{
	assert(m_Resources.size() < INT_MAX);
	return (int) m_Resources.size();
}

bool DirectoryContainer::v_open(void) noexcept
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
		return readDirectory(m_Path);
	}
	catch (const std::exception e) {
		PDE_ERROR << "Error while reading " << m_Path.string() << "': " << e.what();
		return false;
	}

	return false;
}

std::string DirectoryContainer::v_getResourceName(int i) const noexcept
{
	if (i >= (int) m_Resources.size()) {
		PDE_WARN << "Trying to fetch non-existing resource index: " << i;
		return "";
	}
	(void) i;
	throw std::out_of_range("Unknown resource");
}

int DirectoryContainer::v_getRawResourceSize(Resource *r) noexcept
{
	if (r == nullptr) {
		PDE_ASSERT(r != nullptr, "Resource pointer is nullptr");
		return ParameterNullPointer;
	}

	auto found = m_Resources.find(r->getName());

	if (found == m_Resources.end()) {
		PDE_WARN << "Trying to get size of non-existing resource: " << r->getName();
		return UnknownResource;
	}

	PDE_TRACE << "Returning resource " << r->getName() << " size as " << found->second.second;
	return found->second.second;
}

int DirectoryContainer::v_loadRawResource(Resource *r, char *buffer) noexcept
{
	if (r == nullptr) {
		PDE_ASSERT(r != nullptr, "Resource pointer is nullptr");
		return ParameterNullPointer;
	}

	auto found = m_Resources.find(r->getName());

	if (found == m_Resources.end()) {
		PDE_ERROR << "trying to load non-existing resource: " << r->getName();
		return UnknownResource;
	}

	PDE_TRACE << "Loading resource " << r->getName();

	auto path = found->second.first;
	auto size = found->second.second;

	try  {
		auto file = std::shared_ptr<std::ifstream>(
			new std::ifstream(path.string(), std::ios::in | std::ios::binary | std::ios::ate),
			[=](std::ifstream *ptr) {
			    if (ptr != nullptr && ptr->is_open()) {
				    ptr->close();
			    }
			    safeDelete(ptr);
			});

		if (file->is_open()) {
			PDE_ASSERT(file->tellg() == (unsigned int)size, "Filesize missmatch");

			file->seekg(0, file->beg);
			file->read(buffer, size);
			if (!(*file)) {
				PDE_ERROR << "Error readng " << path.string() << ", only " << file->gcount() << "bytes read";
			}
			else {
				return size;
			}
		}
	}
	catch (const std::exception &e) {
		PDE_FATAL << "Caught exception while reading file: " << e.what();
		PDE_EXIT_FAILURE("Exiting due to unhandled exception");
	}
	return ReadFailure;
}

bool DirectoryContainer::readDirectory(fs::path dir) noexcept
{
	PDE_ASSERT(fs::is_directory(dir), "not a directory");

	std::vector<fs::path> subdirs;

	PDE_TRACE << "Reading directory " << dir.string();


	for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator(); ++it) {
		if (fs::is_directory(it->path())) {
			PDE_TRACE << "Found subdirectory " << it->path().string();
			subdirs.push_back(*it);
		}
		else {
			auto entry = std::make_pair(it->path(), fs::file_size(*it));

			std::string resourceName = it->path().string();
			resourceName.erase(0, m_Path.parent_path().string().length() + 1);
			resourceName = Resource(resourceName).getName();

			//auto r = Resource(resourceName);

			PDE_TRACE << "Registering resource [" << resourceName << "] (size: " << entry.second <<
			          ")";

			if (m_Resources.find(resourceName) != m_Resources.end()) {
				PDE_ERROR << "Duplicate resorce encountered [" << resourceName << "]";
				assert(false);
			}
			m_Resources[resourceName] = entry;
		}
	}

	for (auto d : subdirs) {
		readDirectory(d);
	}

	return true;
}

}

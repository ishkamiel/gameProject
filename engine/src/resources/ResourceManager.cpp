#include "resources/ResourceManager.h"

#include "app/Config.h"
#include "resources/ResourceCache.h"
#include "resources/DefaultResourceLoader.h"
#include "resources/DirectoryContainer.h"
#include "utils/Logger.h"

#include <boost/filesystem.hpp>

#include "pugixml.hpp"

#include <memory>

namespace pdEngine
{

std::shared_ptr<ResourceManager> ResourceManager::get(void) noexcept
{
	static auto raw = new ResourceManager();
	static auto pointer = std::shared_ptr<ResourceManager>(raw);
	return pointer;
}

ResourceManager::ResourceManager(void)
{
	m_resourceCache = std::unique_ptr<ResourceCache>(new ResourceCache(100));
}

ResourceManager::~ResourceManager(void)
{ }

unsigned int ResourceManager::getCacheSize() const noexcept
{
	return m_resourceCache->getCacheSize();
}

unsigned int ResourceManager::getAllocatedCacheSize() const noexcept
{
	return m_resourceCache->getAllocated();
}

bool ResourceManager::addContainer(const std::string &containerName)
{
	boost::filesystem::path path{Config::get()->getRootDirectoryPath()};
	path /= Config::get()->getString("resources.root");
	path /= containerName;

	if (boost::filesystem::is_directory(path)) {
		PDE_DEBUG << "Adding DirectoryContainer " << containerName;
		m_resourceCache->addContainer(std::make_shared<DirectoryContainer>(path.string()));
		return true;
	}

	PDE_ERROR << "Unable to find supported resouce container for " << containerName;
	return false;
}


void ResourceManager::requestResource(const std::string &resource)
{
	PDE_NOT_IMPLEMENTED_FATAL();
	// TODO
}

void ResourceManager::requestXML(const std::string &resource)
{
	PDE_NOT_IMPLEMENTED_FATAL();
	// TODO
}

std::shared_ptr<ResourceHandle> ResourceManager::loadResource(const std::string &res) noexcept
{
	return m_resourceCache->getHandle(std::make_shared<Resource>(res));
}

std::shared_ptr<pugi::xml_document> ResourceManager::loadXML(const std::string &res) noexcept
{
	auto handle = m_resourceCache->getHandle(std::make_shared<Resource>(res));
	auto doc = std::make_shared<pugi::xml_document>();
	//pugi::xml_document doc ;
	pugi::xml_parse_result result = doc->load_buffer(handle->getBuffer(), handle->getSize());
	if (result) {
		PDE_INFO << "XML Resource " << handle->getName() << " successfully parsed";
	}
	else {
		PDE_FATAL << "XML Resource " << handle->getName() << " parsed with errors!";
		PDE_FATAL << "\tError description: " << result.description();
		PDE_FATAL << "\tError offset: " << result.offset;
	}
	return doc;
}

void ResourceManager::onInit() noexcept
{
	m_resourceCache->registerLoader(ResourceLoader_sptr(new DefaultResourceLoader()));
	readyToRun();
}

void ResourceManager::onUpdate(int delta) noexcept
{
	(void) delta;
}


}

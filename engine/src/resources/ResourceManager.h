#pragma once

#include "tasks/Task.h"
#include "utils/Deprecated.h"
#include <memory>

namespace pugi
{
class xml_document;
}

namespace pdEngine
{

class ResourceManager;

using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
using ResourceManager_wptr = std::weak_ptr<ResourceManager>;

class ResourceCache;

class XMLResourceHandle;

class ResourceHandle;

class ResourceManager : public Task
{
	std::unique_ptr<ResourceCache> m_resourceCache;

public:
	static std::shared_ptr<ResourceManager> get(void) noexcept;

	virtual ~ResourceManager(void);

	std::string v_getTaskName(void) const noexcept override
	{ return "Resource Manager"; }

	unsigned int getCacheSize() const noexcept;
	unsigned int getAllocatedCacheSize() const noexcept;

	bool addContainer(const std::string &filename);

	DEPRECATED(pugi::xml_document *loadResourceXML(const std::string &resource));

	/**
	 * @brief Schedule a resource to be loaded. When the resource has been loaded into memory a
	 * ResourceLoadedEvent will be fired. If resource cannot be found a ResourceNotFoundEvent is
	 * fired instead.
	 */
	void requestResource(const std::string &resource);

	/**
	 * @brief Schedules the loading of resource and creating of XML DOM. Fires either a
	 * ResourceLoadedEvent on completion, or ResourceNotFoundEvent if resource not found.
	 */
	void requestXML(const std::string &resource);

	/**
	 * @brief Returns a ResourceHandle to a loaded resource. Note that this will, if needed, cause
	 * a possibly costly load of the resources.
	 */
	std::shared_ptr<ResourceHandle> loadResource(const std::string &resource) noexcept;


	/**
	 * @brief Load XML document. Note, this could be quite costly, in addition to possibly loading
	 * the raw resource this requires construction of the XML DOM.
	 */
	std::shared_ptr<pugi::xml_document> loadXML(const std::string &resource) noexcept;

protected:
	void onUpdate(int deltaMs) noexcept override;
	void onInit(void) noexcept override;
private:
	ResourceManager(void);

	std::unique_ptr<ResourceCache> rc;
};

}

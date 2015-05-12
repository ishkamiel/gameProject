#pragma once

#include "resources/I_ResourceContainer.h"
#include "resources/I_ResourceLoader.h"
#include "resources/Resource.h"
#include "resources/ResourceHandle.h"

#include <list>
#include <map>
#include <memory>


namespace pdEngine
{

//! A fixed size resource cache to manage resource loading
/*!
 * The resource cache manages loading of resources from one or more I_ResourceContainer objects.
 * Loading is done with provided I_ResourceLoader objects. Loaded resources are returned in
 * ResourceHandle objects that provide access to the raw memory buffer. The resource cache has a
 * fixed size and freeing and memory allocations are tracked through the handle objects, so their
 * timely destruction is required.
 */
class ResourceCache
{

protected:
	std::list<ResourceHandle_sptr> m_lruResources;
	std::map<std::string, ResourceHandle_sptr> m_resources;
	std::list<ResourceLoader_sptr> m_loaders;
	std::list<ResourceContainer_sptr> m_containers;

	unsigned int m_cacheSize;
	unsigned int m_allocated;

public:
	//! Construct cache of size MB.
	ResourceCache(const unsigned int size);

	//! Destructor
	/*! Destructing the cache does not invalidate handles, but will destroy all internal
	 * references to handles.
	 */
	virtual ~ResourceCache();

	//! Change cache size.
	void setCacheSizeMB(unsigned int size);

	//! Get the size maximum memory allocated by the cache.
	unsigned int getCacheSize(void) const noexcept
	{ return m_cacheSize; }

	//! Get the currently allocated memory.
	unsigned int getAllocated(void) const noexcept
	{ return m_allocated; }


	//! Resets ResourceCache.
	/*! Removes all internal resource handles. Removes any added
	 * containers and loaders. Does not guarantee any resources are released, onyly that the
	 * cache releases it's references.
	 */
	void reset(void) noexcept;

	//! Release all internal ResourceHandles.
	void clear(void);

	//! Add a resource container.
	bool addContainer(ResourceContainer_sptr);

	//! Register a resource loader.
	bool registerLoader(ResourceLoader_sptr);

	//! Get handle to a resource.
	/*! This will, if needed, cause a possibly costly load of the resource.
	 */
	ResourceHandle_sptr getHandle(std::shared_ptr<Resource>);

	//! Preload a resource.
	int preLoad(const std::string pattern, void (*callback)(int, bool &));

protected:
	ResourceHandle_sptr find(std::shared_ptr<Resource>);
	ResourceHandle_sptr load(std::shared_ptr<Resource>);

	void update(ResourceHandle_sptr);

	/**
	 * NOTE this won't guarantee any released memory!
	 * This simply removes the internal ResourceHandle pointer reference, which might trigger
	 * the destructor. Memory is released only when the handle destructor notifies the resource
	 * cache.
	*/
	void free(ResourceHandle_sptr);

	bool makeRoom(unsigned int);
	char *allocate(unsigned int);
	void freeOneResource();
	void memoryHasBeenFreed(unsigned int);

private:
	// helper functions for cleaner code
	ResourceContainer_sptr getContainer(std::shared_ptr<Resource> r) noexcept;
	ResourceLoader_sptr getLoader(std::shared_ptr<Resource> r) noexcept;
	ResourceHandle *loadRaw(ResourceContainer_sptr, ResourceLoader_sptr, std::shared_ptr<Resource>);
	ResourceHandle *loadNonRaw(
		ResourceContainer_sptr, ResourceLoader_sptr, std::shared_ptr<Resource>);
};

using ResourceCache_sptr = std::shared_ptr<ResourceCache>;
using ResourceCache_wptr = std::weak_ptr<ResourceCache>;
}


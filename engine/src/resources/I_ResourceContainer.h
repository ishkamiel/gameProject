#pragma once

#include "resources/Resource.h"

#include <memory>

namespace pdEngine
{
class I_ResourceContainer
{
public:
	virtual ~I_ResourceContainer(void)
	{ };

	/**
	 * @brief Returns an identifier for the specific container
	 * object
	 *
	 * @return string representing the name of the object
	 */
	virtual std::string v_getName(void) const noexcept = 0;

	/**
	 * @brief Open the associated resource file.
	 *
	 * @return true if everything went okay, otherwise false.
	 */
	virtual bool v_open(void) = 0;

	/**
	 * @brief Returns the raw size of a given Resource.
	 *
	 * @param res Resource that is being fetched.
	 *
	 * @return size of the resource.
	 */
	virtual int v_getRawResourceSize(std::shared_ptr<Resource> resource) = 0;

	/**
	 * @brief Reads the requested resource raw data into memory
	 *
	 * @param res Resource that is being fetched.
	 * @param buf Block of memory where the stuff will be placed.
	 *
	 * @return Number of bytes read.
	 */
	virtual int v_loadRawResource(std::shared_ptr<Resource> resource, char *buffer) = 0;

	/**
	 * @brief Fetch the number of resources contained in File.
	 *
	 * @return Number of resources.
	 */
	virtual int v_getResourceCount(void) const = 0;

	/**
	 * @brief Fetch the resource name of a resource as indexed by number.
	 *
	 * @param num Index of resource.
	 *
	 * @return Name of resource.
	 */
	virtual std::string v_getResourceName(int num) const = 0;
};

using ResourceContainer_sptr = std::shared_ptr<I_ResourceContainer>;
using ResourceContainer_uptr = std::unique_ptr<I_ResourceContainer>;

}

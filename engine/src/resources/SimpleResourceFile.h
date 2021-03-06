#ifndef SIMPLERESOURCEFILE_H_
#define SIMPLERESOURCEFILE_H_

#include "resources/Resource.h"

#include <fstream>
#include <memory>
#include <string>

#include "I_ResourceContainer.h"

namespace pdEngine
{

class SimpleResourceFile : public I_ResourceContainer
{
public:
	/**
	 *
	 * @brief Creates a new iResourceFile consisting of a single file with
	 * a single resource.
	 *
	 * @param std::string filename
	 */
	SimpleResourceFile(const std::string &);
	virtual ~SimpleResourceFile();

	virtual std::string v_getName() const noexcept override;

	virtual bool v_open(void) noexcept override;
	virtual int v_getResourceCount(void) const noexcept override;
	virtual std::string v_getResourceName(int) const noexcept override;
	virtual int v_getRawResourceSize(Resource *) noexcept override;
	virtual int v_loadRawResource(Resource *, char *) noexcept override;

private:
	std::string filename;
	std::string resourceName;
	int rawSize;
	std::unique_ptr<std::ifstream> m_File;
};

}
#endif /* SIMPLERESOURCEFILE_H_ */

#ifndef SIMPLERESOURCEFILE_H_
#define SIMPLERESOURCEFILE_H_ 

#include "resources/Resource.h"

#include <fstream>
#include <memory>
#include <string>

#include "I_ResourceContainer.h"

namespace pdEngine
{

class SimpleResourceFile: public I_ResourceContainer
{
public:
	/**
	 *
	 * @brief Creates a new iResourceFile consisting of a single file with
	 * a single resource.
	 *
	 * @param std::string filename
	 */
	SimpleResourceFile(const std::string&);
	virtual ~SimpleResourceFile();

	virtual std::string v_getName() const noexcept override;

	virtual bool vOpen(void) override;
	virtual int vGetNumResources(void) const override;
	virtual std::string vGetResourceName(int) const override;
	virtual int vGetRawResourceSize(const Resource&) override;
	virtual int vGetRawResource(const Resource&, char*) override;

private:
	std::string filename;
	std::string resourceName;
	int rawSize;
	std::unique_ptr<std::ifstream> m_File;
};

}
#endif /* SIMPLERESOURCEFILE_H_ */

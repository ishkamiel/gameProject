/*
 * DirectoryContainer.h
 *
 *  Created on: Apr 13, 2015
 *      Author: ishkamiel
 */

#ifndef DIRECTORYCONTAINER_H_
#define DIRECTORYCONTAINER_H_

#include "I_ResourceContainer.h"

#include <list>

namespace pdEngine
{

class DirectoryContainer: public I_ResourceContainer
{
public:
	DirectoryContainer(const std::string& path);
	virtual ~DirectoryContainer();

	virtual bool vOpen(void) override;
	virtual int vGetNumResources(void) const override;
	virtual std::string vGetResourceName(int) const override;
	virtual int vGetRawResourceSize(const Resource&) override;
	virtual int vGetRawResource(const Resource&, char*) override;

private:
	std::string m_Path;
	std::list<std::pair<std::string,size_t>> m_Resources;
};

} /* namespace pdEngine */

#endif /* DIRECTORYCONTAINER_H_ */

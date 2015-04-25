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

	virtual bool v_open(void) override;
	virtual int v_getResourceCount(void) const override;
	virtual std::string v_getResourceName(int) const override;
	virtual int v_getRawResourceSize(std::shared_ptr<Resource>) override;
	virtual int v_loadRawResource(std::shared_ptr<Resource>, char *) override;

private:
	std::string m_Path;
	std::list<std::pair<std::string,size_t>> m_Resources;
};

} /* namespace pdEngine */

#endif /* DIRECTORYCONTAINER_H_ */

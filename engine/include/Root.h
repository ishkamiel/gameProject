/*
 *  Root.h
 *
 *  Created on: Apr 12, 2015
 *      Author: ishkamiel
 */

#ifndef ROOT_H_
#define ROOT_H_

#include "events/EventManager.h"
#include "resources/ResourceManager.h"

#include <memory>

namespace pdEngine
{

class Root
{
	Root();
	virtual ~Root();

	std::shared_ptr<EventManager> getEventManager() const noexcept;
	std::shared_ptr<ResourceManager> getResourceManager() const noexcept;
};

std::shared_ptr<Root> getRoot(void) noexcept;

}
#endif /* ROOT_H_ */

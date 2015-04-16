/*
 * DirectoryContainer.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: ishkamiel
 */

#include "resources/DirectoryContainer.h"

#include <stdexcept>

namespace pdEngine
{

DirectoryContainer::DirectoryContainer(const std::string& path)
{
	// TODO Auto-generated constructor stub
}

DirectoryContainer::~DirectoryContainer()
{
	// TODO Auto-generated destructor stub
}


int DirectoryContainer::vGetNumResources(void) const {
    return 0;
}

bool DirectoryContainer::vOpen(void) {
    return false;
}

std::string DirectoryContainer::vGetResourceName(int i) const {
    (void) i;
    throw std::out_of_range("Unknown resource");
}

int DirectoryContainer::vGetRawResourceSize(Resource const &r) {
    (void) r;
    throw std::out_of_range("Unknown resource");
}

int DirectoryContainer::vGetRawResource(Resource const &r, char *buffer) {
    (void) r;
    (void) buffer;
    throw std::out_of_range("Unknown resource");
}

} /* namespace pdEngine */

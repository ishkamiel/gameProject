#include "resources/Resource.h"

#include <algorithm>

namespace pdEngine
{
    Resource::Resource(const std::string& n)
        : name(n)
    {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower); 
    }

    Resource::~Resource()
    {}

    const std::string Resource::getName(void) const
    {
        return name;
    }
}

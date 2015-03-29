#ifndef PDENGINE_RESOURCE_H_
#define PDENGINE_RESOURCE_H_ value

#include <string>

namespace pdEngine
{
    class Resource
    {
    public:
        std::string name;

    public:
        Resource(const std::string& name);
        ~Resource();
        const std::string getName(void);
    };
}
#endif

#include "resources/SimpleResourceFile.h"

#include "Utils.h"

#include <cassert>
#include <fstream>
#include <iostream>

namespace pdEngine
{
    SimpleResourceFile::SimpleResourceFile (const std::string& filename)
        : filename(filename)
    {
        Resource res { filename };
        resourceName = res.getName();
    }

    SimpleResourceFile::~SimpleResourceFile(void)
    {
        if (file != nullptr && file.is_open())
        {
            file.close();
        }
    }

    bool SimpleResourceFile::vOpen(void)
    {
        std::ifstream file(filename, std::ios::in|std::ios::binary|std::ios::ate);
        if (file.is_open())
        {
            rawSize = file.tellg();
            isOpen = true;
            return true;
        }
        getLogger()->warn("Unable to open file {0} for reading", filename);
        return false;
    }

    int SimpleResourceFile::vGetRawResourceSize(const Resource &r)
    {
        if (!isOpen) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            getLogger()->warn("Cannot find resource: {0}, in resource {1}", r.getName(), filename);
            throw std::out_of_range("Unknown resource");
        }
        (void)r;

        return rawSize;
    }

    int SimpleResourceFile::vGetRawResource(const Resource &r, char *buffer)
    {
        if (!isOpen) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            getLogger()->warn("Cannot find resource: {0}, in resource {1}", r.getName(), filename);
            throw std::out_of_range("Unknown resource");
        }

        (void)r;
        file.seekg(0, std::ios::beg);
        file.read(buffer, rawSize);
        return rawSize;
    }

    int SimpleResourceFile::vGetNumResources() const
    {
        if (!isOpen) throw std::logic_error("Resource not opened");
        if (isOpen)
        {
            return 1;
        }
        return 0;
    }

    std::string SimpleResourceFile::vGetResourceName(int num) const
    {
        if (!isOpen) throw std::logic_error("Resource not opened");
        assert(num == 0);
        (void)num;
        return filename;
    }
}

#include "resources/SimpleResourceFile.h"

#include "Logger.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

namespace pdEngine
{
    SimpleResourceFile::SimpleResourceFile (const std::string& filename)
        : filename(filename), resourceName(filename), rawSize(0), file(nullptr)
    {
        std::transform(resourceName.begin(), resourceName.end(), resourceName.begin(), ::tolower); 
    }

    SimpleResourceFile::~SimpleResourceFile(void)
    {
        if (file != nullptr && file->is_open())
        {
            file->close();
            delete file;
        }
    }

    bool SimpleResourceFile::vOpen(void)
    {
        file = new std::ifstream(filename, std::ios::in|std::ios::binary|std::ios::ate);
        if (file->is_open())
        {
            rawSize = file->tellg();
            return true;
        }
        getLogger()->warn("Unable to open file {0} for reading", filename);
        return false;
    }

    int SimpleResourceFile::vGetRawResourceSize(const Resource &r)
    {
        if (file == nullptr || !file->is_open()) throw std::logic_error("Resource not opened");
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
        if (file == nullptr || !file->is_open()) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            getLogger()->warn("Cannot find resource: {0}, in resource {1}", r.getName(), filename);
            throw std::out_of_range("Unknown resource");
        }

        (void)r;
        file->seekg(0, file->beg);
        file->read(buffer, rawSize);
        if (!file)
            getLogger()->error(
                    "Error reading file {0}, got only {1} bytes", filename, file->gcount());

        // getLogger()->warn("reading {0}, got only {1}, bytes", filename, file.gcount());
        // getLogger()->warn("rawSize is {0}, buffer is '{1}'", rawSize, buffer);
        return rawSize;
    }

    int SimpleResourceFile::vGetNumResources() const
    {
        if (file == nullptr || !file->is_open()) throw std::logic_error("Resource not opened");
        return 1;
    }

    std::string SimpleResourceFile::vGetResourceName(int num) const
    {
        if (file == nullptr || !file->is_open()) throw std::logic_error("Resource not opened");
        if (num != 0)
            throw std::out_of_range("Unknown resource");

        return resourceName;
    }
}

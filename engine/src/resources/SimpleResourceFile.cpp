#include "resources/SimpleResourceFile.h"

#include "Utils.h"

#include <cassert>
#include <fstream>
#include <iostream>

namespace pdEngine
{
    SimpleResourceFile::SimpleResourceFile (const std::string& filename)
        : filename(filename)
    {}

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
            return true;
        }
        getLogger()->warn("Unable to open file {0} for reading", filename);
        return false;
    }

    int SimpleResourceFile::vGetRawResourceSize(const Resource &r)
    {
        assert(r.getName() == filename);
        (void)r;

        return rawSize;
    }

    int SimpleResourceFile::vGetRawResource(const Resource &r, char *buffer)
    {
        assert(r.getName() == filename);
        (void)r;

        file.seekg(0, std::ios::beg);
        file.read(buffer, rawSize);
        return rawSize;
    }

    int SimpleResourceFile::vGetNumResources() const
    {
        return 1;
    }

    std::string SimpleResourceFile::vGetResourceName(int num) const
    {
        assert(num == 0);
        (void)num;
        return filename;
    }
}

#include "resources/SimpleResourceFile.h"

#include "Logger.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

namespace pdEngine
{
    SimpleResourceFile::SimpleResourceFile (const std::string& filename)
        : filename(filename), resourceName(filename), rawSize(0)
    {
        std::transform(resourceName.begin(), resourceName.end(), resourceName.begin(), ::tolower); 
    }

    SimpleResourceFile::~SimpleResourceFile(void)
    {
        if (m_File && m_File->is_open())
        {
            m_File->close();
        }
    }

    bool SimpleResourceFile::vOpen(void)
    {
        m_File.reset(new std::ifstream(filename, std::ios::in|std::ios::binary|std::ios::ate));
        if (m_File->is_open())
        {
            rawSize = m_File->tellg();
            return true;
        }
        warn("Unable to open file {0} for reading", filename);
        return false;
    }

    int SimpleResourceFile::vGetRawResourceSize(const Resource &r)
    {
        if (m_File == nullptr || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            warn("Cannot find resource: {0}, in resource {1}", r.getName(), filename);
            throw std::out_of_range("Unknown resource");
        }
        (void)r;

        return rawSize;
    }

    int SimpleResourceFile::vGetRawResource(const Resource &r, char *buffer)
    {
        if (m_File == nullptr || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            warn("Cannot find resource: {0}, in resource {1}", r.getName(), filename);
            throw std::out_of_range("Unknown resource");
        }

        (void)r;
        m_File->seekg(0, m_File->beg);
        m_File->read(buffer, rawSize);
        if (!m_File)
            error("Error reading file {0}, got only {1} bytes", filename, m_File->gcount());

        // getLogger()->warn("reading {0}, got only {1}, bytes", filename, file.gcount());
        // getLogger()->warn("rawSize is {0}, buffer is '{1}'", rawSize, buffer);
        return rawSize;
    }

    int SimpleResourceFile::vGetNumResources() const
    {
        if (!m_File || !m_File->is_open()) throw std::logic_error("Resource not opened");
        return 1;
    }

    std::string SimpleResourceFile::vGetResourceName(int num) const
    {
        if (!m_File || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (num != 0)
            throw std::out_of_range("Unknown resource");

        return resourceName;
    }
}

#include "resources/SimpleResourceFile.h"

#include "utils/Logger.h"

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

    bool SimpleResourceFile::v_open(void)
    {
        m_File.reset(new std::ifstream(filename, std::ios::in|std::ios::binary|std::ios::ate));
        if (m_File->is_open())
        {
            rawSize = m_File->tellg();
            return true;
        }

        PDE_WARN << "Unable to open file {0} for reading" << filename;
        return false;
    }

    int SimpleResourceFile::v_getRawResourceSize(const Resource &r)
    {
        if (m_File == nullptr || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            PDE_WARN << "Cannot find resource " << r.getName() << " in " << filename;
            throw std::out_of_range("Unknown resource");
        }
        (void)r;

        return rawSize;
    }

    int SimpleResourceFile::v_loadRawResource(const Resource &r, char *buffer)
    {
        if (m_File == nullptr || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (r.getName() != resourceName) 
        {
            PDE_WARN << "Cannot find resource " << r.getName() << " in " << filename;
            throw std::out_of_range("Unknown resource");
        }

        (void)r;
        m_File->seekg(0, m_File->beg);
        m_File->read(buffer, rawSize);
        if (!m_File)
            PDE_ERROR << "Error reading " << filename << ", only " << m_File->gcount() << "bytes read";

        return rawSize;
    }

    int SimpleResourceFile::v_getResourceCount(void) const
    {
        if (!m_File || !m_File->is_open()) throw std::logic_error("Resource not opened");
        return 1;
    }

    std::string SimpleResourceFile::v_getResourceName(int num) const
    {
        if (!m_File || !m_File->is_open()) throw std::logic_error("Resource not opened");
        if (num != 0)
            throw std::out_of_range("Unknown resource");

        return resourceName;
    }

std::string SimpleResourceFile::v_getName(void) const noexcept
{
    return filename;
}

}

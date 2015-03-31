#ifndef SIMPLERESOURCEFILE_H_
#define SIMPLERESOURCEFILE_H_ 

#include "resources/iResourceFile.h"
#include "resources/Resource.h"

#include <fstream>
#include <string>

namespace pdEngine
{
    class SimpleResourceFile : public iResourceFile
    {
        std::string filename;
        std::string resourceName;
        int rawSize;
        std::ifstream file;
        bool isOpen { false };

    public:
        SimpleResourceFile(const std::string&);
        virtual ~SimpleResourceFile();

        virtual bool vOpen(void) override;
        virtual int vGetNumResources(void) const override;
        virtual std::string vGetResourceName(int) const override;
        virtual int vGetRawResourceSize(const Resource&) override;
        virtual int vGetRawResource(const Resource&, char*) override;
    };
}

#endif /* SIMPLERESOURCEFILE_H_ */

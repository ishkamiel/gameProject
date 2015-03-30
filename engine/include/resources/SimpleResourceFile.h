#ifndef SIMPLERESOURCEFILE_H_
#define SIMPLERESOURCEFILE_H_ 

#include "resources/iResourceFile.h"

#include <fstream>
#include <string>

namespace pdEngine
{
    class SimpleResourceFile : public iResourceFile
    {
        std::string filename;
        int rawSize;
        std::ifstream file;

    public:
        SimpleResourceFile(const std::string&);
        virtual ~SimpleResourceFile();

        virtual bool vOpen(void) override;
        virtual int vGetRawResourceSize(const Resource&) override;
        virtual int vGetRawResource(const Resource&, char*) override;
        virtual int vGetNumResources(void) const override;
        virtual std::string vGetResourceName(int) const override;
    };
}

#endif /* SIMPLERESOURCEFILE_H_ */

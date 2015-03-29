#ifndef SIMPLERESOURCEFILE_H_
#define SIMPLERESOURCEFILE_H_ 

#include "resources/iResourceFile.h"

#include <fstream>

namespace pdEngine
{
    class SimpleResourceFile : public iResourceFile
    {
        std::string filename;
        int rawSize;
        std::ifstream file;

    public:
        SimpleResourceFile (const std::string&);
        virtual ~SimpleResourceFile();

        virtual bool vOpen() override;
        virtual int vGetRawResourceSize(const Resource &r) override;
        virtual int vGetRawResource(const Resource &r, char *buffer) override;
        virtual int vGetNumResources() const override;
        virtual std::string vGetResourceName(int num) const override;
    
    protected:
    
    private:
    };
}

#endif /* SIMPLERESOURCEFILE_H_ */

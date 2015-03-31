#ifndef IRESOURCEFILE_H_
#define IRESOURCEFILE_H_ value

#include "resources/Resource.h"

namespace pdEngine
{
    class iResourceFile
    {
    public:
        /**
         * @brief Open the associated resource file.
         *
         * @return true if everything went okay, otherwise false.
         */
        virtual bool vOpen(void) =0;
        /**
         * @brief Returns the raw size of a given Resource.
         *
         * @param res Resource that is being fetched.
         *
         * @return size of the resource.
         */
        virtual int vGetRawResourceSize(const Resource &res) =0;
        /**
         * @brief Reads the requested resource raw data into memory
         *
         * @param res Resource that is being fetched.
         * @param buf Block of memory where the stuff will be placed.
         *
         * @return Number of bytes read.
         */
        virtual int vGetRawResource(const Resource &res, char *buf)= 0;
        /**
         * @brief Fetch the number of resources contained in File.
         *
         * @return Number of resources.
         */
        virtual int vGetNumResources(void) const =0;
        /**
         * @brief Fetch the resource name of a resource as indexed by number.
         *
         * @param num Index of resource.
         *
         * @return Name of resource.
         */
        virtual std::string vGetResourceName(int num) const =0;
    };
}

#endif /* IRESOURCEFILE_H_ */   

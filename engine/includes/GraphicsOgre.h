#ifndef PDENGINE_OGREGRAPHICS_H_
#define PDENGINE_OGREGRAPHICS_H_

#include "General.h"
#include "IGraphics.h"

#include "OgreCommon.h"
#include "OgreRoot.h"
#include "OgreResourceGroupManager.h"

namespace pdEngine 
{

    class GraphicsOgre : public IGraphics
    {
        typedef Ogre::NameValuePairList VideoOptions;

        Ogre::Root root;

    public:
        virtual ~GraphicsOgre();
        virtual bool init() override;
        virtual bool start() override;

    private:
        VideoOptions getVideoOptions();
    };
}

#endif /* PDENGINE_OGREGRAPHICS_H_ */

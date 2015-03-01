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
		GraphicsOgre();
        ~GraphicsOgre();
		
        bool init() override;
        bool start() override;
        void shutdown() override;

    private:
        VideoOptions getVideoOptions();
    };
}

#endif /* PDENGINE_OGREGRAPHICS_H_ */

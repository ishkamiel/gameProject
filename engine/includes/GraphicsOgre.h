#ifndef PDENGINE_OGREGRAPHICS_H_
#define PDENGINE_OGREGRAPHICS_H_

#include "General.h"
#include "IGraphics.h"

#include "OgreRoot.h"
#include "CEGUISystem.h"

namespace pdEngine 
{

    class GraphicsOgre : public IGraphics
    {
        typedef Ogre::NameValuePairList VideoOptions;

        Ogre::Root*             	ogreRoot        { nullptr };
        Ogre::RenderWindow*     	ogreWindow      { nullptr };
        Ogre::SceneManager*     	guiSceneManager { nullptr };
		
		CEGUI::OgreCEGUIRenderer*	guiRenderer;
		CEGUI::System*				guiSystem;

    public:
		GraphicsOgre();
        ~GraphicsOgre();
		
        bool init() override;
        bool start() override;
        void shutdown() override;

    private:
        VideoOptions getVideoOptions();
		
		bool setRenderSystem(VideoOptions&);
		
		bool showGUI();
    };
}

#endif /* PDENGINE_OGREGRAPHICS_H_ */

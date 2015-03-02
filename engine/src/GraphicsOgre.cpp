#include "GraphicsOgre.h"

#include "pdLogger.h"

#include "OgreCommon.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreResourceGroupManager.h"

#include "CEGUIFontManager.h"
#include "CEGUILogger.h"
#include "CEGUISchemeManager.h"

namespace pdEngine 
{
	GraphicsOgre::GraphicsOgre()
	{}
	
    GraphicsOgre::~GraphicsOgre()
    {
		//PD_DELETE(guiSystem);
		//PD_DELETE(guiRenderer);
		//PD_DELETE(guiSceneManager);
		//PD_DELETE(ogreWindow);
		PD_DELETE(ogreRoot);
    }

    bool GraphicsOgre::init()
    {
        ogreRoot = new Ogre::Root();
        try {

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    "resource", "FileSystem", "General");

            VideoOptions options = getVideoOptions();

			if (! setRenderSystem(options))
				return false;

            ogreRoot->initialise(false);
            ogreWindow = ogreRoot->createRenderWindow("prutt", 640, 400, false, &options);

            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            guiSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);

            //showGui();
        }
        catch (Ogre::Exception &e) {
            std::string msg = e.getFullDescription();
            std::cerr << msg << std::endl;
            exit (-1);
        }

        return(true);
    }

    bool GraphicsOgre::start()
    {
        return(true);
    }

    void GraphicsOgre::shutdown()
    {
    }

    GraphicsOgre::VideoOptions GraphicsOgre::getVideoOptions()
    {
        VideoOptions options;

        std::map<std::string, std::string> defaultOptions {
            { "FSAA", "0" },
                { "colourDepth", "32" },
                { "fullscreen", "false" },
                { "renderSystem", "openGL" },
                { "resolution", "640x400" },
                { "vsync", "true" }
        };

        std::for_each(defaultOptions.begin(), defaultOptions.end(), 
                [&options](std::pair<std::string, std::string> pair) 
                {
                options.insert(VideoOptions::value_type(pair.first, pair.second));
                });

        return options;
    }
    
    bool GraphicsOgre::setRenderSystem(VideoOptions& options)
	{
        Ogre::RenderSystemList::iterator r_it;
 
        std::string val { options.find("renderSystem")->second };
        Ogre::RenderSystemList renderSystems = ogreRoot->getAvailableRenderers();
		
        for (r_it=renderSystems.begin(); r_it!=renderSystems.end(); r_it++) {
            Ogre::RenderSystem *tmp = *r_it;
            std::string rName(tmp->getName());
 
            if ((int) rName.find(val) >= 0) {
                ogreRoot->setRenderSystem(*r_it);
				return(true);
            }
        }
        log()->error("Unable to find RenderSystem");
        
        return(false);        
	}
	
	bool GraphicsOgre::showGUI()
	{
		/*
		guiRenderer = new CEGUI::OgreCEGUIRenderer(ogreWindow, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, guiSceneManager);
		guiSystem = new CEGUI::System(guiRenderer);
		CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
		CEGUI::SchemeManager::getSingleton().
		CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
		guiSystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
		
		CEGUI::FontManager::getSingleton().createFont("bluehighway.font");
		guiSystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
		
		// set the mouse cursor initially in the middle of the screen
		guiSystem->injectMousePosition((float)ogreWindow->getWidth() / 2.0f, (float)ogreWindow->getHeight() / 2.0f);
		*/
	}
	
}

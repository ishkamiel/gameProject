#include "GraphicsOgre.h"

namespace pdEngine 
{
	GraphicsOgre::GraphicsOgre()
	{}
	
    GraphicsOgre::~GraphicsOgre()
    {
        if (ogreRoot != nullptr)
        {
            delete ogreRoot;
        }
    }

    bool GraphicsOgre::init()
    {
        ogreRoot = new Ogre::Root();
        try {

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    "resource", "FileSystem", "General");

            VideoOptions options = getVideoOptions();

            //Ogre::RenderSystemList* renderSystems = nullptr;
            //Ogre::RenderSystemList::iterator r_it;

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
}

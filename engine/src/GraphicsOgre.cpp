#include "GraphicsOgre.h"

namespace pdEngine 
{
	GraphicsOgre::GraphicsOgre()
	{}
	
    GraphicsOgre::~GraphicsOgre()
    {}

    bool GraphicsOgre::init()
    {
        //root = new Ogre::Root("", "");

        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                "resource", "FileSystem", "General");


        return(true);
    }

    bool GraphicsOgre::start()
    {
        return(true);
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

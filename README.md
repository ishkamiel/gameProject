gameProject
===========

Goals
-----

The goal of this project is to build an extendable game engine and some simple
game to demo it. This project was initiated during the Game Project Course at
the Helsinki University, but the intent is to, time permitting, continue this
work outside that scope. In it's current state the project includes mostly
completed event, resource, configuratoin and process management. The project is
build with CMake, and does include testing with Google Test/Mock. Some external
utility libraries are used, but otherwise everything is built from the ground
up, and as such this serves mostly as a learning exercise.


Structure
---------

The project uses CMake as it's build system and is organized in separate demo
and engine subprojects. The engine also includes tests for some of the more
fundamental parts of the engine, and allows selective running and building of
thests. Code documentation is inlined with the header files, use the doxygen
format and can be build with the build system.

- `demo`

   demo source, assets and configuration files  

- `engine/config`

   engine configuration files (configured by CMake)  

- `engine/resources`

   engine "build-in" assests (currently only testing files)  

- `engine/src`

   engine source and headers  

- `engine/tes`

   engine test source code  

- `misc`

   Misc stuff.  

External libraries
------------------

- [Boost](http://www.boost.org)
- [Epoxy](https://github.com/anholt/libepoxy)
- [pugixml](http://pugixml.org) 


Prerequesites
-------------


The project relies on libepoxy for OpenGL handling, pugixml for xml parsin,
gtest and gmock for testing and on various Boost libraries for logging,
filesystem and config management. The build system will automatically download
pugixml, gtest and gmock, but both Boost and libepoxy need to be installed on
the build system.

For ubuntu the prerequsites can be installed like so:

````shell
apt-get install libboost-log-dev libboost-program-options-dev libboost-filesystem-dev libepoxy-dev
````


Building
--------

The project uses CMake for building. In order to build the project in the
current working directory simply call cmake with the project directory as an
argument. Starting from the project root the following commands builds the
project in the build subdirectory:

````shell
mkdir build
cd build
cmake ..
make
````

The test and demo binaries should afterwards be found in the bin directory. In
order to build documentation simply issue:

````shell
make doc
````

Current State
-------------

The following parts of the whole are kind of done:

- EventManager implemented with tests.
- TaskManager implemented with tests.
- ResourceManager/Cache implemented for XML and raw files. Tested.
- Configuration management built upon Boost::Config.
- Simplistic logging and error management done.
- A very duridmentary start for a rendering system and scenegraph on OpenGL.
- A general architecture to tie this stuff together.
- A CMake build system to manage dependencies and builds.

The demo program itself currently does essentially nothing, and will not
actually build. The basic subsystems are properly initialized and the mainloop
is entered, but there currently is no game in there. Input and event management
is limited to proper shtudown on handling closing of the window (pressing the X
on the window).  While rendering is/was working at some point, the current work
on the scenegraph and rendering is unfinished.

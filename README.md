gameProject
===========

Goals
-----

The ultimate goal of this project is to build an extendable game engine and a
tower defence game to demo it. Within the scope of the related Game Project
Course the initial aim was to create the an event manager system and task
manager system, and then using simple SDL 2D graphics build a simple demo game.
However, due to serious underestimation of the work required, I also included
the implementation of 3D rendering, proper resource management and
confiugration management. Most of the systems and architecture implemented is
heavily inspired by by Mike McShaffry's book Game Coding Complete. Becuase the
aim is to create a reusable and extensible system, much effort has also been
put into an easy to use build system.

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
````.

Current State
-------------

The following parts of the whole are kind of done:

- EventManager implemented with tests.
- TaskManager implemented with tests.
- ResourceManager/Cache implemented for XML and raw files. Tested.
- Configuration management built upon Boost::Config.
- Simplistic logging and error management done.
- A very duridmentary start for a rendering system and scenegraph on OpenGL.
- A general architecture to tie these stuff together.
- A CMake build system to manage dependencies and builds.

The demo program itself currently does essentially nothing. The basic
subsystems are properly initialized and the mainloop is entered, but there
currently is no game in there. Input and event management is limited to proper
shtudown on handling closing of the window (pressing the X on the window).
While rendering is/was working at some point, the current work on the
scenegraph and rendering is unfinished.

While the project is in a clearly unfinished state and the game itself is
non-existant, the implemented systems are in a quite satisfacotry state.

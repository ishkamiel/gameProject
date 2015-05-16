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


Current State
-------------


Building
--------

The project uses CMake for building. In order to build the project in the current working
directory simply call cmake with the project directory as an argument. Starting from the project
root the following commands builds the project in the build subdirectory:

````shell
mkdir build
cd build
cmake ..
make
````

In order to build documentation simply issue ````make doc````. 

Prerequesites
-------------

The project relies on libepoxy for OpenGL handling, pugixml for xml parsin, gtest and gmock for 
testing and on various Boost libraries for logging, filesystem and config management. 

Required insta



Personal
--------

This is a personal project and as such, you probably shouldn't be here.

TODO
----

- [x] Plan for project end
- [x] Resource directory containers
- [x] Resource xml loading
- [ ] Actor factory
- [ ] Actor placeholder compoenent (rotating cube)
- [ ] Render something
- [ ] Camera movement
- [ ] Actor movement (simple movement logic)
- [ ] Blank surfaces
- [ ] Tiled map
- [ ] Mouse click input
- [ ] Tower placeholder actors
- [ ] Change movement to account towers

External libraries
------------------

- [Boost](http://www.boost.org)
- [Epoxy](https://github.com/anholt/libepoxy)
- [pugixml](http://pugixml.org)

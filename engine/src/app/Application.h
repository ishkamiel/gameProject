#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <GL/glut.h>

#include <memory>

namespace pdGame
{
	class Application;

    using AppPtrS = std::shared_ptr<Application>;

    class Application
    {
        public:

            friend AppPtrS pdGame::getMainWindow(std::string windowName);

            ~Application();

            bool initialize(int*, char**);
            bool start();
            int getHeight();
            int getWidth();
        private:
            Application(std::string);

            std::string windowName;
    };

    AppPtrS getMainWindow(std::string windowName);
}

#endif

#include "Application.h"

namespace pdGame
{
    AppPtrS getMainWindow(std::string windowName)
    {
        static AppPtrS appWindow {
            new Application(windowName)
        };
        return (appWindow);
    }


    Application::~Application() {}

    void renderScene(void) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
        glEnd();

        glutSwapBuffers();
    }


    bool Application::initialize(int *argc, char **argv)
    {
        //glutInit(&argc, argv);
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(320,320);

        return (true);
    }

    bool Application::start()
    {
        glutCreateWindow(windowName.c_str());

        // register callbacks
        glutDisplayFunc(renderScene);

        // enter GLUT event processing cycle
        glutMainLoop();

        return (true);
    }

    Application::Application(std::string windowName)
        : windowName(windowName)
    {}
}

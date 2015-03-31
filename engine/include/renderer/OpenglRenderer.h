#ifndef PDENGINE_RENDEREROPENGL_H_
#define PDENGINE_RENDEREROPENGL_H_

#include "renderer/Renderer.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL.h>
#include <SDL_opengl.h> 

namespace pdEngine
{
    class OpenglRenderer : public Renderer
    {
        int window_width                { 640 };
        int window_height               { 480 };
        std::string windowTitle         { "pdEngine" };

        SDL_Window* window              { nullptr };

        SDL_GLContext   glContext;
        SDL_Window*     glWindow;
        GLuint          programID               { 0 }; 

        bool            gRenderQuad             { true };
        GLint           gVertexPos2DLocation    { -1 }; 
        GLuint          gVBO                    { 0 };
        GLuint          gIBO                    { 0 };

    public:
        OpenglRenderer(std::string = "pdEngine");
        ~OpenglRenderer();

        virtual void render(void) const override;
        virtual void printDebugMsg(std::string) override;

    protected:
        virtual void onInit() override;
        virtual void onUpdate(TimeDelta) override;

    private:
        bool initOpengl(void);
    };
}



#endif /* PDENGINE_RENDEREROPENGL_H_ */

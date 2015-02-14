#ifndef RENDERER_H
#define RENDERER_H

namespace pdGame
{
    public:
        Renderer GetAndInitializeRenderer();
        Renderer GetAndInitializeRenderer(
                const int width,
                const int height);

        class Renderer;
        {
            public:

            private:
                RendererImplementation *rendererPimpl;

                Renderer(int width, int height);
                Renderer();
        }

    private:
        extern class Rendererimplementation;
}

#endif

#pragma once
#include<C:\mingw_dev_lib\include\SDL2\SDL.h>

class Drawing{
    public:
        //The window renderer
        static SDL_Renderer* gRenderer;
        //global reference to png image sheets
        static SDL_Texture* assets;
};
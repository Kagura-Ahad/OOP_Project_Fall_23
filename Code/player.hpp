#include<C:\mingw_dev_lib\include\SDL2\SDL.h>
#include <C:\mingw_dev_lib\include\SDL2\SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
//#include "game.hpp"

class Vampire {
    private:
    SDL_Texture* vampireTexture;
    SDL_Rect vampireRect;

    public:
    Vampire();
    ~Vampire();

    void loadTexture(SDL_Renderer* gRenderer, const char* path);
    void render(SDL_Renderer* gRenderer, int x, int y );
    void move(int x, int y);
};
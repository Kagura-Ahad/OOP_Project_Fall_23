#include<C:\mingw_dev_lib\include\SDL2\SDL.h>
#include <C:\mingw_dev_lib\include\SDL2\SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 832;
    const int SCREEN_HEIGHT = 468;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    

public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
};
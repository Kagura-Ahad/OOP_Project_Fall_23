#include "player.hpp"

Vampire::Vampire() {
    vampireTexture = NULL;
    vampireRect.x = 0;
    vampireRect.y = 0;
    vampireRect.w = 0;
    vampireRect.h = 0;
}

Vampire::~Vampire() {
    SDL_DestroyTexture(vampireTexture);
    vampireTexture = NULL;
}

void Vampire::loadTexture(SDL_Renderer* gRenderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        vampireRect.w = surface->w;
        vampireRect.h = surface->h;
    }

    vampireTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Vampire::render(SDL_Renderer* gRenderer, int x, int y ) {
    SDL_Rect renderQuad = { x, y, vampireRect.w, vampireRect.h };
    SDL_RenderCopy(gRenderer, vampireTexture, NULL, &renderQuad);
}

void Vampire::move(int x, int y) {
    vampireRect.x = x;
    vampireRect.y = y;
}
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>

#include "player.hpp"
#include "world.hpp"
#include "camera.hpp"

struct AppContext {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* messageTex, *imageTex;
    SDL_FRect messageDest;
    SDL_AudioDeviceID audioDevice;
    Mix_Music* music;
    SDL_AppResult app_quit = SDL_APP_CONTINUE;
    Player* player;
    World* world;
    TTF_Font* font;
    std::filesystem::path basePath;
    Pos camera;
};
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <string_view>
#include <filesystem>
#include <map>

#include "appcontext.hpp"

using std::pair;
using std::map;

float scale = 0;
void setScale(void* appstate) {
    auto* app = (AppContext*)appstate;
    int width, height, bbwidth, bbheight;
    SDL_GetWindowSize(app->window, &width, &height);
    SDL_GetWindowSizeInPixels(app->window, &bbwidth, &bbheight);
    scale = float(width) / 500;
    SDL_Log("Scale: %f", scale);
}

map<char, pair<SDL_Texture*, bool>> textureCache;
void renderWorld(void* appstate) {
    auto* app = (AppContext*)appstate;

    vector<vector<char>> worldState = renderWorld(*(app->world));
    for (int y = 0; y < worldState.size(); y++) {
        vector<char> line = worldState.at(y);
        for (int x = 0; x < line.size(); x++) {
            char blockChar = line.at(x);
            SDL_Texture* messageTex;
            if (textureCache.contains(blockChar)) {
                messageTex = textureCache.at(blockChar).first;
            } 
            else {
                SDL_Surface* surface;
                Block block = (*app->world).getBlockRegistry().getByEncoding(blockChar);
                string texturePath = (app->basePath / "assets/textures/").string() + block.getId().path_ + ".png";
                bool isText = true;
                if (std::filesystem::exists(texturePath)) {
                    isText = false;
                    // load the SVG
                    surface = IMG_Load(texturePath.c_str());
                }
                else {
                    std::string_view block_str = string(1, blockChar);
                    surface = TTF_RenderText_Solid(app->font, block_str.data(), block_str.size(), { 255,255,255 });
                }
                // make a texture from the surface
                messageTex = SDL_CreateTextureFromSurface(app->renderer, surface);
                SDL_SetTextureScaleMode(messageTex, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
                
                SDL_DestroySurface(surface);
                textureCache.insert({blockChar, {messageTex, isText}});
            }
            auto messageTexProps = SDL_GetTextureProperties(messageTex);
            SDL_FRect text_rect{
                .x = float(x * 16 * scale)+3 + app->camera.x,
                .y = float(y * 16 * scale) + app->camera.y,
                .w = float(10 * scale),
                .h = float(16 * scale)
            };
            SDL_FRect texture_rect{
                .x = float(x * 16 * scale) + app->camera.x,
                .y = float(y * 16 * scale) + app->camera.y,
                .w = float(16 * scale),
                .h = float(16 * scale)
            };
            bool isText = textureCache.at(blockChar).second;
            
            SDL_RenderTexture(app->renderer, messageTex, NULL, isText ? &text_rect : &texture_rect);
        }
    }
}
map<string, SDL_Texture*> playerTextureCache;
void renderPlayer(void* appstate) {
    auto* app = (AppContext*)appstate;
    BlockPos playerPos = (*app->player).getPos();
    
    string state = "idle";
    if ((*app->player).isFreeFalling()) state = "falling";
    if (!(*app->player).isAlive()) state = "dead";
    SDL_Texture* messageTex;
    if (playerTextureCache.contains(state)) {
        messageTex = playerTextureCache.at(state);
    } 
    else {
        SDL_Surface* surface;
        string texturePath = (app->basePath / "assets/textures/").string() + "player_"+ state + ".png";
        if (std::filesystem::exists(texturePath)) {
            // load the SVG
            surface = IMG_Load(texturePath.c_str());
        }
        // make a texture from the surface
        messageTex = SDL_CreateTextureFromSurface(app->renderer, surface);
        SDL_SetTextureScaleMode(messageTex, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
        
        SDL_DestroySurface(surface);
        playerTextureCache.insert({state, messageTex});
    }
    auto messageTexProps = SDL_GetTextureProperties(messageTex);
    SDL_FRect text_rect{
        .x = float((playerPos.getX()-0.5) * 16 * scale) + app->camera.x,
        .y = float(playerPos.getY() * 16 * scale) + app->camera.y,
        .w = float(32 * scale),
        .h = float(32 * scale)
    };
    
    SDL_RenderTexture(app->renderer, messageTex, NULL, &text_rect);
}

bool enteredNextWorld = false;
auto smoothStartTime = 0;
int targetCameraX = 0;
void setCameraPos(void* appstate) {
    auto* app = (AppContext*)appstate;
    auto time = SDL_GetTicks() / 100000.f;

    int lastCameraX = app->camera.x;
    targetCameraX = -(std::max(0, app->player->getPos().getX() - 5)) * 16 * scale;
    if (!enteredNextWorld) {
        if (lastCameraX != app->camera.x) smoothStartTime = time;
        app->camera.x = lastCameraX + (targetCameraX - lastCameraX) * std::min(1.0f, (time - smoothStartTime) * 0.25f);
    }
    else {
        app->camera.x = targetCameraX;
        enteredNextWorld = false;
    }
}
#pragma once
#include <SDL3/SDL.h>

const Uint32 playerDeathEvent = SDL_RegisterEvents(1);
static SDL_Event ADVENTURA_DEATH_EVENT;

static void registerEvents() {
    if (playerDeathEvent != 0) {
        SDL_Event event;
        SDL_zero(ADVENTURA_DEATH_EVENT);
        ADVENTURA_DEATH_EVENT.type = playerDeathEvent;
        ADVENTURA_DEATH_EVENT.user.code = 1;
        SDL_PushEvent(&event);
    }
}
static void emitDeathEvent() {
    SDL_PushEvent(&ADVENTURA_DEATH_EVENT);
}
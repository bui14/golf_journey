#include "music.h"

void music::playMusic(const char* filePath,int times)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_Music* music = Mix_LoadMUS(filePath);
    if (music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, times);

    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

}

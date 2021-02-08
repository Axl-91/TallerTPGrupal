#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL_Sounds.h"
#include <iostream>
#include <string>

SDL_Sounds* SDL_Sounds::soundInstance = 0;

SDL_Sounds::SDL_Sounds(){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);

    loadChunk("Media/SoundEffects/sfxmenu2.wav");
    loadChunk("Media/SoundEffects/sfxmenu1.wav");
    loadChunk("Media/SoundEffects/STAB.wav");
    loadChunk("Media/SoundEffects/GUNSHT.wav");
    loadChunk("Media/SoundEffects/GUNSHT2.wav");
    loadChunk("Media/SoundEffects/GUNSHT3.wav");
    loadChunk("Media/SoundEffects/rocket.wav");
    loadChunk("Media/SoundEffects/BJAAH.wav");
    loadChunk("Media/SoundEffects/BJGRUNT.wav");
    loadChunk("Media/SoundEffects/BJDIE.wav");
    loadChunk("Media/SoundEffects/EPAIN.wav");
    loadChunk("Media/SoundEffects/EDIE.wav");

    loadMusic("Media/Music/xdeath.ogg");
    loadMusic("Media/Music/xevil.ogg");
    loadMusic("Media/Music/zerohour.ogg");
    loadMusic("Media/Music/ultimate.ogg");
}

void SDL_Sounds::loadChunk(std::string nameChunk){
    Mix_Chunk* chunkLoad = Mix_LoadWAV(nameChunk.c_str());
    Mix_VolumeChunk(chunkLoad, 50);
    if (chunkLoad == 0){
        std::cout << "Error loading chunk: " << Mix_GetError() << std::endl;
    }
    vectorChunks.push_back(chunkLoad);
}

void SDL_Sounds::loadMusic(std::string nameMusic){
    Mix_Music* musicLoad = Mix_LoadMUS(nameMusic.c_str());
    if (musicLoad == 0){
        std::cout << "Error loading music: " << Mix_GetError() << std::endl;
    }
    vectorMusic.push_back(musicLoad);
}

void SDL_Sounds::playEffect(int type){
    Mix_PlayChannel(-1, vectorChunks[type], 0);
}

void SDL_Sounds::playMusic(int type){
    Mix_PlayMusic(vectorMusic[type], -1);
}

void SDL_Sounds::stopMusic(){
    Mix_HaltMusic();
}

SDL_Sounds::~SDL_Sounds(){
    for (int i; i < vectorChunks.size(); i++){
        Mix_FreeChunk(vectorChunks[i]);
    }
    for (int j; j < vectorMusic.size(); j++){
        Mix_FreeMusic(vectorMusic[j]);
    }
    Mix_CloseAudio();
    Mix_Quit();
}

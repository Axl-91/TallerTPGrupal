#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL_Sounds.h"
#include <iostream>
#include <string>

SDL_Sounds* SDL_Sounds::soundInstance = 0;

SDL_Sounds::SDL_Sounds(): 
    fileSFX("Media/SoundEffects/SoundEffects.txt"),
    fileMusic("Media/Music/Music.txt")
    {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);

    std::vector<std::string> vectorAux;

    vectorAux = fileSFX.getVectorFiles();
    for (std::string fileName : vectorAux){
        loadChunk(fileName);
    }

    vectorAux = fileMusic.getVectorFiles();
    for (std::string fileName : vectorAux){
        loadMusic(fileName);
    }
}

void SDL_Sounds::loadChunk(std::string &nameChunk){
    Mix_Chunk* chunkLoad = Mix_LoadWAV(nameChunk.c_str());
    if (chunkLoad == 0){
        std::cout << "Error loading chunk: " << Mix_GetError() << std::endl;
    }
    vectorChunks.push_back(chunkLoad);
}

void SDL_Sounds::loadMusic(std::string &nameMusic){
    Mix_Music* musicLoad = Mix_LoadMUS(nameMusic.c_str());
    if (musicLoad == 0){
        std::cout << "Error loading music: " << Mix_GetError() << std::endl;
    }
    vectorMusic.push_back(musicLoad);
}

void SDL_Sounds::playEffect(const int &type, const int &vol){
    Mix_VolumeChunk(vectorChunks[type], vol);
    Mix_PlayChannel(-1, vectorChunks[type], 0);
}

void SDL_Sounds::playMusic(const int &type, const int &vol){
    Mix_VolumeMusic(vol);
    Mix_PlayMusic(vectorMusic[type], -1);
}

void SDL_Sounds::stopMusic(){
    Mix_HaltMusic();
}

void SDL_Sounds::freeVectors(){
    for (int i; i < vectorChunks.size(); i++){
        Mix_FreeChunk(vectorChunks[i]);
    }
    vectorChunks.clear();
    for (int j; j < vectorMusic.size(); j++){
        Mix_FreeMusic(vectorMusic[j]);
    }
    vectorMusic.clear();
}

void SDL_Sounds::close(){
    delete soundInstance;
    soundInstance = 0;
}

SDL_Sounds::~SDL_Sounds(){
    freeVectors();
    Mix_CloseAudio();
    Mix_Quit();
}

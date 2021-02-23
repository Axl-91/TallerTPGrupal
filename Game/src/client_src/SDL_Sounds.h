#ifndef _SDL_SOUNDS_
#define _SDL_SOUNDS_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include "FilesHandler.h"

enum SOUNDS {
    MENU_MOVE, MENU_SELECT, KNIFE_STAB, GUN_SHOT, RIFLE_SHOT,
    MINIGUN_SHOT, ROCKET_SHOT, PLAYER_HEAL, PLAYER_HURT, PLAYER_DIE,
    ENEMY_HURT, ENEMY_DIE
};
enum MUSIC {
    MENU_MUSIC, GAME_MUSIC1, GAME_MUSIC2, GAME_MUSIC3
};

class SDL_Sounds{

public:
    static SDL_Sounds* getInstance() {
        if (soundInstance == 0){
            soundInstance = new SDL_Sounds();
        }
        return soundInstance;
    }
    void playEffect(const int &type, const int &vol);
    void playMusic(const int &type, const int &vol);
    void stopMusic();
    void close();
    
private:
    static SDL_Sounds* soundInstance;
    FilesHandler fileSFX;
    FilesHandler fileMusic;
    std::vector<Mix_Chunk*> vectorChunks;
    std::vector<Mix_Music*> vectorMusic;
    SDL_Sounds();
    void loadChunk(std::string &nameChunk);
    void loadMusic(std::string &nameMusic);
    void freeVectors();
    ~SDL_Sounds();
};

#endif

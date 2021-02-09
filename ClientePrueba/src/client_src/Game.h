#ifndef __GAME__
#define __GAME__

#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <atomic>
#include "Player.h"
#include "Map.h"
#include "../common_src/types.h"
#include "../common_src/thread.h"
#include "../common_src/protectedQueue.h"

//
//Clase que se ocupa de la logica del renderizado
class Game : public Thread{
private:
    int largoReal = 320;
    int altoReal = 240;
	bool gameOver = false;
	int winLargo;
	int winAlto;
	Map mapGame;
	Player player;
	SDL_Window* window;
	SDL_Renderer* renderer;
    void fill();
	ProtectedQueue<Update_t> &uQ;
    std::atomic<bool> is_running;
public:
	Game(int largo, int ancho, std::vector<std::vector<int>> &lvl, ProtectedQueue<Update_t> &q);
	~Game();
	void operator()();
    virtual void run() override;
    void stop();
	void updatePlayer(Player_t &player);
    // void setFullScreen();
	void render();
	void update();
	bool isGameOver();
	void quitGame();
	SDL_Renderer* getRenderer();
	void updateMap(Map_change_t &aMapChange);
};

#endif
#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "CollisionMap.h"
#include "Player.h"
#include "Map.h"
#include "SDL_EventHandler.h"

class Game{
private:
    int largoReal = 320;
    int altoReal = 240;
	bool gameOver = false;
	int winLargo;
	int winAlto;
	Map mapGame;
	CollisionMap colMap;
	Player player;
	SDL_Window* window;
	SDL_Renderer* renderer;
	// void exitPollEvent(SDL_Event &evento);
    void fill();
	void movePlayer(player_orientation_t orientation);

public:
	Game(int largo, int ancho, std::vector<std::vector<int>> &lvl);
	~Game();

	void receiveEvent(event_t event);

	void handleCollision(circle &playerPos, int c);
    void setFullScreen();
	void render();
	// void pollEvent();
	bool isGameOver();
	SDL_Renderer* getRenderer();
};

#endif
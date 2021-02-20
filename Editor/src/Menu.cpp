#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "SDLHandler.h"
#include "TextHandler.h"
#include "Defines.h"

Menu::Menu() : splash(0, 0, 320, 240, MENU_SPLASH),
			   mainMenu(0, 0, 320, 240, MENU_MAIN),
			   mainCreate(0, 0, 320, 240, MENU_CREATE),
			   mainEdit(0, 0, 320, 240, MENU_EDIT),
			   optionsMenu(0, 0, 320, 240, MENU_OPTION),
			   selection(0, 0, 23, 33, MENU_SEL),
			   main(0, 0, 320, 240, MENU_MAP),
			   save(0, 0, 160, 120, MENU_SAVE),
			   textNameHandler(" "),
			   textMapHandler(" ")
{
	initialize();
	createText();
}

void Menu::createText(){
	SDL_Surface *surfaceText;
	TTF_Font *font = TTF_OpenFont("beamweapon.ttf", 28);

	surfaceText = TTF_RenderText_Blended(font, "On", yellow);
	on = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "Off", yellow);
	off = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "640x480", yellow);
	resOne = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "800x600", yellow);
	resTwo = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	surfaceText = TTF_RenderText_Blended(font, "1024x768", yellow);
	resThree = SDL_CreateTextureFromSurface(menuRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);
}

void Menu::initialize(){
	int existError;
	existError = SDL_Init(SDL_INIT_VIDEO);
	if (existError){
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
	}

	existError = SDL_CreateWindowAndRenderer(winlenght, winhigh,
										   SDL_RENDERER_ACCELERATED, &menuWindow, &menuRenderer);
	if (existError){
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
	}

	SDL_SetWindowTitle(menuWindow, "Game Editor");
	SDL_RenderSetLogicalSize(menuRenderer, lenght, high);
	TTF_Init();

	map.setRenderer(menuRenderer);
	splash.setRenderer(menuRenderer);
	mainMenu.setRenderer(menuRenderer);
	optionsMenu.setRenderer(menuRenderer);
	selection.setRenderer(menuRenderer);
	main.setRenderer(menuRenderer);
	mainCreate.setRenderer(menuRenderer);
	mainEdit.setRenderer(menuRenderer);
	save.setRenderer(menuRenderer);
	textNameHandler.setRenderer(menuRenderer, white);
	textMapHandler.setRenderer(menuRenderer, white);

	selection.setSrc(0, 0, 23, 16);	

	vectorMaps = sett.getMaps();	
	mapelement = vectorMaps[0];
}

void Menu::renderTextCreate(bool printDinamic){
	if (printDinamic){
		if (nameChange){
			if (mapname.size() == 0){
				textNameHandler.setText(" ");
			}
			else{
				textNameHandler.setText(mapname);
			}
			nameChange = false;
		}
		int sizeName = 7 * mapname.size();
		textNameHandler.render(180, 78, sizeName, 15);
	}
}

void Menu::renderTextEdit(){
	if(vectorMaps.size() != 0){
		if (mapChange){
			textMapHandler.setText(vectorMaps[mapPos]);
			mapChange = false;
		}
		int mapNameSize = 7*vectorMaps[mapPos].size();		
		textMapHandler.render(posVectorX,posVectorY,mapNameSize,15);
	} 
}

void Menu::renderTextOptions(){
	SDL_Rect res_rect = {175, 75, 45, 15};
	SDL_Rect switch_rect = {175, 100, 15, 15};

	if (winlenght == 640){
		SDL_RenderCopy(menuRenderer, resOne, NULL, &res_rect);
	}
	else if (winlenght == 800){
		SDL_RenderCopy(menuRenderer, resTwo, NULL, &res_rect);
	}
	else if (winlenght == 1024){
		SDL_RenderCopy(menuRenderer, resThree, NULL, &res_rect);
	}

	if (isFullScreen){
		SDL_RenderCopy(menuRenderer, on, NULL, &switch_rect);
	}
	else{
		SDL_RenderCopy(menuRenderer, off, NULL, &switch_rect);
	}
}

void Menu::renderMenu(){
	if (menu == SPL){
		splash.render(0, 0, 320, 240);
	}else if (menu == MAIN){
		mainMenu.render(0, 0, 320, 240);
		selection.render(70, posSelectMain, 23, 16);
	}else if (menu == OPTIONS){
		optionsMenu.render(0, 0, 320, 240);
		selection.render(70, posSelectOpt, 23, 16);
		renderTextOptions();
	}else if (menu == MAP){
		main.render(0, 0, 320, 240);
		map.render();
	}else if (menu == CREATE){
		mainCreate.render(0, 0, 320, 240);
		selection.render(70, posSelectCrt, 23, 16);
		renderTextCreate(true);
	}else if (menu == EDIT){
		mainEdit.render(0, 0, 320, 240);
		selection.render(70, posSelectEdt, 23, 16);
		renderTextEdit();
	}else if (menu == SAV){
		save.render(80, 60, 160, 120);
		selection.render(100, posSelectSave, 23, 16);
	}
}

void Menu::renderCreateForInput(std::string &input, int x, int y){
	SDL_RenderClear(menuRenderer);

	mainCreate.render(0, 0, 320, 240);
	selection.render(70, posSelectCrt, 23, 16);
	renderTextCreate(false);

	if (input.size() > 0){
		TextHandler handler(input);
		handler.setRenderer(menuRenderer, yellow);
		int sizeName = 7 * input.size();
		handler.render(x, y, sizeName, 15);
	}
	SDL_RenderPresent(menuRenderer);
	SDL_RenderClear(menuRenderer);
}

void Menu::render(){
	renderMenu();
	SDL_RenderPresent(menuRenderer);
}

bool Menu::inputText(std::string &input, int x, int y){
	bool hasChange = false;

	bool exit = false;
	SDL_StartTextInput();
	SDL_Event event;
	while (!exit){
		bool renderText = false;
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_TEXTINPUT && input.size() < 15){
				input += event.text.text;
				renderText = true;
			}
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
				case SDLK_RETURN:
					exit = true;
					hasChange = true;
					renderText = false;
					break;
				case SDLK_ESCAPE:
					exit = true;
					break;
				case SDLK_BACKSPACE:
					if (input.size() > 0)
					{
						input.pop_back();
						renderText = true;
					}
					break;
				}
			}
		}
		if (renderText){
			renderCreateForInput(input, x, y);
		}
	}
	SDL_StopTextInput();
	return hasChange;
}

void Menu::doActionMain(){
	switch (posSelectMain){
	case MAIN_CREATE:
		posSelectCrt = CRT_NAME;
		menu = CREATE;
		break;
	case MAIN_OPTIONS:
		menu = OPTIONS;
		posSelectOpt = OPT_RES;
		break;
	case MAIN_EDIT:
		menu = EDIT;
		break;
	case MAIN_EXIT:
		hasQuitGame = true;
		break;
	}
}

void Menu::doActionCreate(){
	switch (posSelectCrt){
	case CRT_NAME:
		nameChange = inputText(mapname, 180, 78);
		break;
	case CRT_PLA:

		break;
	case CRT_NEW:
		sett.init(mapname);
		map.init(sett, mapname, true);
		menu = MAP;
		break;
	}
}

void Menu::doActionEdit(){
	switch (posSelectEdt){
	case EDT_MAP:
			selectMap();
		break;
	case EDT_IN:
		map.init(sett, mapelement, false);
		menu = MAP;
		break;
	}
}

void Menu::renderSelectionMap(int &pos){
	SDL_RenderClear(menuRenderer);
	mainEdit.render(0, 0, lenght, high);
	selection.render(70, posSelectEdt, 23, 16);

	if (vectorMaps.size() > 0){
		TextHandler handler(vectorMaps[pos]);
		handler.setRenderer(menuRenderer, yellow);
		int sizeJoin = 7*vectorMaps[pos].size();
		handler.render(posVectorX,posVectorY,sizeJoin,15);
	} 
	SDL_RenderPresent(menuRenderer);
}

void Menu::selectMap(){
	bool selected = false;
	SDL_Event event;
	renderSelectionMap(mapPos);

	while (!selected){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
					case SDLK_RIGHT:
						if (vectorMaps.size() > mapPos+1){
							mapPos += 1;
							renderSelectionMap(mapPos);
						}
						break;
					case SDLK_LEFT:
						if (mapPos > 0){
							mapPos -= 1;
							renderSelectionMap(mapPos);
						}
						break;
					case SDLK_RETURN:
						if (vectorMaps.size() > 0){
							mapelement = vectorMaps[mapPos];
							mapChange = true;
							selected = true;
						}
						break;
					case SDLK_ESCAPE:
						selected = true;						
						break;
				}
			}
		}
	}
}

void Menu::doActionSave(){
	switch (posSelectSave){
	case SAVE_S:
		sett.saveChanges(map.getMap(),map.getMapName());
		sett.UpdateFiles();
		vectorMaps = sett.getMaps();	
		mapelement = vectorMaps[0];
		break;
	case SAVE_Q:
		break;
	}
	mapname = "";
	nameChange = true;
	menu = MAIN;
}

void Menu::doActionOpt(){
	switch (posSelectOpt){
	case OPT_RES:
		if (winlenght == 640){
			winlenght = 800;
			winhigh = 600;
		}
		else if (winlenght == 800){
			winlenght = 1024;
			winhigh = 768;
		}
		else if (winlenght == 1024){
			winlenght = 640;
			winhigh = 480;
		}
		SDL_SetWindowSize(menuWindow, winlenght, winhigh);
		break;
	case OPT_FS:
		if (!isFullScreen){
			SDL_SetWindowFullscreen(menuWindow, SDL_WINDOW_FULLSCREEN);
			isFullScreen = true;
		}
		else{
			SDL_SetWindowFullscreen(menuWindow, 0);
			SDL_SetWindowSize(menuWindow, winlenght, winhigh);
			isFullScreen = false;
		}
		break;
	case OPT_BACK:
		menu = MAIN;
		break;
	}
}

void Menu::pollEventMain(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			hasQuitGame = true;
			break;
		case SDLK_DOWN:
			if (posSelectMain != MAIN_EXIT){
				posSelectMain += 25;
			}
			else{
				posSelectMain = MAIN_CREATE;
			}
			break;
		case SDLK_UP:
			if (posSelectMain != MAIN_CREATE){
				posSelectMain -= 25;
			}
			else{
				posSelectMain = MAIN_EXIT;
			}
			break;
		case SDLK_RETURN:
			doActionMain();
			break;
		}
	}
}

void Menu::pollEventSplash(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		menu = MAIN;
	}
}

void Menu::pollEventOptions(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			menu = MAIN;
			break;
		case SDLK_DOWN:
			if (posSelectOpt != OPT_BACK){
				posSelectOpt += 25;
			}
			else{
				posSelectOpt = OPT_RES;
			}
			break;
		case SDLK_UP:
			if (posSelectOpt != OPT_RES){
				posSelectOpt -= 25;
			}
			else{
				posSelectOpt = OPT_BACK;
			}
			break;
		case SDLK_RETURN:
			doActionOpt();
			break;
		}
	}
}

void Menu::pollEventMap(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			menu = SAV;
			break;
		}
	}
	map.setResolution(winlenght, winhigh);
	map.pollEvent(event);
}

void Menu::pollEventCreate(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			menu = MAIN;
			break;
		case SDLK_DOWN:
			if (posSelectCrt != CRT_NEW){
				posSelectCrt += 25;
			}
			else{
				posSelectCrt = CRT_NAME;
			}
			break;
		case SDLK_UP:
			if (posSelectCrt != CRT_NAME){
				posSelectCrt -= 25;
			}
			else{
				posSelectCrt = CRT_NEW;
			}
			break;
		case SDLK_RETURN:
			doActionCreate();
			break;
		}
	}
}

void Menu::pollEventSave(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			menu = MAP;
			break;
		case SDLK_DOWN:
			if (posSelectSave == SAVE_S){
				posSelectSave = SAVE_Q;
			}
			else{
				posSelectSave = SAVE_S;
			}
			break;
		case SDLK_UP:
			if (posSelectSave == SAVE_S){
				posSelectSave = SAVE_Q;
			}
			else{
				posSelectSave = SAVE_S;
			}
			break;
		case SDLK_RETURN:
			doActionSave();
			break;
		}
	}
}

void Menu::pollEventEdit(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_ESCAPE:
			menu = MAIN;
			break;
		case SDLK_DOWN:
			if (posSelectEdt == EDT_MAP){
				posSelectEdt = EDT_IN;
			}
			else{
				posSelectEdt = EDT_MAP;
			}
			break;
		case SDLK_UP:
			if (posSelectEdt == EDT_MAP){
				posSelectEdt = EDT_IN;
			}
			else{
				posSelectEdt = EDT_MAP;
			}
			break;
		case SDLK_RETURN:
			doActionEdit();
			break;
		}
	}
}

void Menu::pollEvent(){
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			hasQuitGame = true;
		}
		else{
			switch (menu){
			case SPL:
				pollEventSplash(event);
				break;
			case MAIN:
				pollEventMain(event);
				break;
			case EDIT:
				pollEventEdit(event);
				break;
			case OPTIONS:
				pollEventOptions(event);
				break;
			case MAP:
				pollEventMap(event);
				break;
			case CREATE:
				pollEventCreate(event);
				break;
			case SAV:
				pollEventSave(event);
				break;
			default:
				break;
			}
		}
	}
}

bool Menu::quitGame(){
	return hasQuitGame;
}

Menu::~Menu(){
	SDL_DestroyTexture(on);
	SDL_DestroyTexture(off);
	SDL_DestroyTexture(resOne);
	SDL_DestroyTexture(resTwo);
	SDL_DestroyTexture(resThree);

	if (menuRenderer){
		SDL_DestroyRenderer(menuRenderer);
		menuRenderer = nullptr;
	}

	if (menuWindow){
		SDL_DestroyWindow(menuWindow);
		menuWindow = nullptr;
	}
	TTF_Quit();
	SDL_Quit();
}

#include "Map.h"

Map::Map():mapHandler(0, 0, 96, 96, "tiles.png")
{}

void Map::render(){
	renderMap();
	renderOptionsMap();
	renderSelected();	
}

void Map::renderSelected(){	
	SDL_Rect selected_rect = {200,200,60,20};
	SDL_RenderCopy(winRenderer, selectedTextura, NULL, &selected_rect);
	SDL_Rect clip = selected.getBox();	
	mapHandler.setSrc(clip.x,clip.y,clip.h,clip.w);
	mapHandler.render(265, 202, TILE_SIZE, TILE_SIZE);	
}

void Map::renderMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    			
		if(checkCollision( camera, (*it).getBox())){
			SDL_Rect clip = tileOptions[(*it).getType()].getBox();
			mapHandler.setSrc(clip.x,clip.y,clip.h,clip.w);
			mapHandler.render((*it).getX() - camera.x, (*it).getY()-camera.y, TILE_SIZE, TILE_SIZE);				
		}
	}
}	

void Map::renderOptionsMap(){
	for (std::vector<Tile>::iterator it = tileOptions.begin() ; it != tileOptions.end(); ++it){		    					
			SDL_Rect clip = (*it).getBox();
			mapHandler.setSrc(clip.x,clip.y,clip.h,clip.w);
			mapHandler.render((*it).getX() + OFFSET_X, (*it).getY() + OFFSET_Y , TILE_SIZE, TILE_SIZE);						
	}	
}

void Map::load(){	
	for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type = map[fil][col];
			Tile tile = Tile(TILE_SIZE*col+x,TILE_SIZE*fil+y,type);						
			tileSet.push_back(tile);
		}
	}	
}

void Map::updateClick(){
	int clickedX = 0, clickedY = 0;
	SDL_GetMouseState(&clickedX, &clickedY);			
	xRelative = clickedX/2;
	yRelative = clickedY/2;
}

void Map::load_objectTiles(){		
	int typeKey = 100;
	int typeEnemy = 108;
	int typeHeal = 110;
	int typeAmmo = 120;	
	int typeWeapon = 130;
	int typeTreasure = 140;
	int typeInmovable = 200;
	int typeDoor = 400;
	int typeWall = 403;
	int type;
	int element = 0;	
	for (int fil = 0; fil < OPTION_ROW; ++fil){
		for (int col = 0; col < OPTION_COL; ++col){
			if(element<=11){
				type = typeWall;
				typeWall++;
			}if((element >11)&&(element<=14)){
				type = typeDoor;
				typeDoor++;
			}if((element >14)&&(element<=17)){
				type = typeHeal;
				typeHeal++;
			}if((element >17)&&(element<=20)){
				type = typeWeapon;
				typeWeapon++;
			}if(element ==21){
				type = typeAmmo;				
			}if(element ==22){
				type = typeEnemy;				
			}if((element >22)&&(element<=29)){
				type = typeInmovable;
				typeInmovable++;
			}if((element >29)&&(element<=33)){
				type = typeTreasure;
				typeTreasure++;
			}if(element >33){
				type = typeKey;
				typeKey++;
			}
			Tile tile = Tile(TILE_SIZE*col,TILE_SIZE*fil,type);						
			tileOptions.push_back(tile);
			element++;
		}
	}
	//inicializo seleccion con el 1er wall posible
	selected = tileOptions[0];
}

void Map::changeSelected(){	
	for (std::vector<Tile>::iterator it = tileOptions.begin() ; it != tileOptions.end(); ++it){		    					
			if((*it).existPosition(xRelative,yRelative,OFFSET_X,OFFSET_Y)){
				selected = (*it);
			}
		}
}

void Map::putTileMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
		if((*it).existPosition(xRelative,yRelative,0,0)){
			 (*it).setType(selected.getType());
		}
	}	
}

void Map::pollEvent(SDL_Event &evento){
	setCamera();
	if(evento.type == SDL_MOUSEBUTTONDOWN){
		if(evento.button.button == SDL_BUTTON_LEFT){
			updateClick();
			changeSelected();
			//putTileMap();
		}
	}
	updateModel();
}

void Map::updateModel(){
	/*for (int fil = rows; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type = map[fil][col];
			Tile tile = Tile(TILE_SIZE*col+x,TILE_SIZE*fil+y,type);						
			tileSet.push_back(tile);
		}
	}*/
}

void Map::initText(){	
	SDL_Surface* surfaceText;
	TTF_Font* font = TTF_OpenFont("beamweapon.ttf", 20);
	SDL_Color yellow = {255, 204, 0};

	surfaceText = TTF_RenderText_Blended(font, "Selected Tile", yellow);
	selectedTextura = SDL_CreateTextureFromSurface(winRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);	
}

void Map::init(Settings &set, SDL_Renderer* _renderer){	
	winRenderer = _renderer;
	mapHandler.setRenderer(winRenderer);

	map = set.getmap();
	rows = map.size();
	columns = map[0].size();		
	std::cout<<rows<<":"<<columns<<std::endl;
	
	initText();
	load();
	load_objectTiles();			
}

void Map::setCamera(){		
    int xOffset = 0, yOffset = 0;    
    SDL_GetMouseState(&xOffset, &yOffset);

	camera.x = (xOffset)- 200/2; 
	camera.y = (yOffset)- 200/2;

	if( camera.x < 0 ){ 
		camera.x = 0;
	}
	if( camera.y < 0 ){
		camera.y = 0;
	}
	if( camera.x > 320 - camera.w )	{
		camera.x = 320 - camera.w;
	}
	if(camera.y > 240 - camera.h ){
		camera.y = 240 - camera.h;
	}
}

bool Map::checkCollision( SDL_Rect a, SDL_Rect b ){    
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    if( bottomA <= topB ){
        return false;
    }

    if( topA >= bottomB ){
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB ) {
        return false;
    }    
    return true;
}

Map::~Map(){}

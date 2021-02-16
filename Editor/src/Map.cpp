#include "Map.h"

Map::Map():mapHandler(0, 0, 384, 384, "tiles.png")
{}

void Map::render(){
	renderMap();
	renderOptionsMap();
	renderSelected();	
}

void Map::setResolution(int _height,int _width){
	scaleX = ((float)_height / 320.0);
	scaleY = ((float)_width / 240.0);
}

void Map::renderSelected(){	
	SDL_Rect selected_rect = {200,200,60,20};	
	SDL_RenderCopy(winRenderer, selectedTextura, NULL, &selected_rect);
	//SDL_Rect clip = selected.getBox();	
	mapHandler.setSrc(selected.getFactx(),selected.getFacty(),TILE_OPTION,TILE_OPTION);
	mapHandler.render(265, 202, TILE_SIZE, TILE_SIZE);	
}

void Map::renderMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
			Tile tile = opt.at((*it).getType());
		//if(checkCollision(camera, clip)){
			mapHandler.setSrc(tile.getFactx(),tile.getFacty(),TILE_OPTION,TILE_OPTION);
			mapHandler.render((*it).getX()+x, (*it).getY()+y, TILE_SIZE, TILE_SIZE);						
		//}
	}
}	

void Map::renderOptionsMap(){
	 for (auto itr = opt.begin(); itr != opt.end(); ++itr) {		
		mapHandler.setSrc((itr->second).getFactx(),(itr->second).getFacty(),TILE_OPTION,TILE_OPTION);
		mapHandler.render((itr->second).getX()+OFFSET_X, (itr->second).getY()+OFFSET_Y, TILE_SIZE, TILE_SIZE);						
    }	
}

void Map::load(){	
	for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type = map[fil][col];
			Tile tile = Tile(TILE_SIZE*col,TILE_SIZE*fil,type,fil,col);						
			tileSet.push_back(tile);
		}
	}	
}

void Map::updateClick(){
	int valx, valy;	
	SDL_GetMouseState(&valx,&valy);	
	xRelative = valx/scaleX;
	yRelative = valy/scaleY;
	//std::cout<<xRelative<<":"<<yRelative<<std::endl;
}

void Map::load_objectTiles(){		
	int typeKey = 101;
	int typeEnemy = 108;
	int typeHeal = 111;
	int typeAmmo = 121;	
	int typeWeapon = 133;
	int typeTreasure = 141;
	int typeInmovable = 201;
	int typeDoor = 400;
	int typeWall = 403;
	int type;
	int element = 0;	
	for (int fil = 0; fil < OPTION_ROW; ++fil){
		for (int col = 0; col < OPTION_COL; ++col){
			if(element == 0){
				type = 0;
			}
			if((element>0)&&(element<=11)){
				type = typeWall;
				typeWall++;
			}if((element>11)&&(element<=14)){
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
			Tile tile = Tile(TILE_SIZE*col,TILE_SIZE*fil,type,fil,col);				
			opt.insert({ type, tile });				
			element++;
		}
	}
	//inicializo seleccion con el 1er wall posible
	selected = opt.at(0);
}

void Map::changeSelected(){		
	for (auto itr = opt.begin(); itr != opt.end(); ++itr) {
		if((itr)->second.existPosition(xRelative,yRelative,OFFSET_X,OFFSET_Y)){
				selected = (itr)->second;
				//std::cout<<"pase"<<std::endl;
			}
    }			
}

void Map::putTileMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
		if((*it).existPosition(xRelative,yRelative,x,y)){
			 (*it).setType(selected.getType());
		}
	}	
}

void Map::pollEvent(SDL_Event &evento){
	updateClick();
	setCamera();

	if(evento.type == SDL_MOUSEBUTTONDOWN){
		if(evento.button.button == SDL_BUTTON_LEFT){									
			changeSelected();
			putTileMap();
		}
	}if ((evento.type == SDL_QUIT)|| 
		(evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE)){			
				updateModel();
	}
}

int Map::getTypebyFilCol(int _fil, int _col){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
		if((*it).existbyFilCol(_fil,_col)){
			return (*it).getType();
		}
	}
	return 0;
}

void Map::updateModel(){
	for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			map[fil][col] = getTypebyFilCol(fil,col);
		}
	}
}

void Map::initText(){	
	SDL_Surface* surfaceText;
	TTF_Font* font_ = TTF_OpenFont("beamweapon.ttf", 24);
	SDL_Color yellow = {255, 204, 0};

	surfaceText = TTF_RenderText_Blended(font_, "Selected Tile", yellow);
	selectedTextura = SDL_CreateTextureFromSurface(winRenderer, surfaceText);	
	SDL_FreeSurface(surfaceText);
}

void Map::init(Settings &set, SDL_Renderer *_renderer){		
	winRenderer = _renderer;
	mapHandler.setRenderer(winRenderer);

	map = set.getmap();
	rows = map.size();
	columns = map[0].size();		

	initText();
	load();
	load_objectTiles();			
}

void Map::setCamera(){		
	camera.x = (xRelative)- camera.w/2; 
	camera.y = (yRelative)- camera.h/2;

	if( camera.x < 15 ){ 
		camera.x = 15;
	}
	if( camera.y < 75 ){
		camera.y = 75;
	}
	/*if( camera.x > 320 - camera.w )	{
		camera.x = 320 - camera.w;
	}
	if(camera.y > 144 - camera.h ){
		camera.y = 144 - camera.h;
	}*/
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
std::vector<std::vector<int>> Map::getMap() const{
	return map;
}

Map::~Map(){}

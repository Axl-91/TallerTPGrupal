#include "Map.h"
#include "Defines.h"

Map::Map():mapHandler(0, 0, 384, 384, "tiles.png"),
		  textPlayerHandler(" "){
	load_objectTiles();	
	players = 0;
}

void Map::render(){
	renderMap();
	renderOptionsMap();
	renderSelected();	
	textPlayerHandler.render(280, 182, 13, 13);	
}

std::string Map::getMapName() const{
	return name;
}

void Map::setResolution(int _height,int _width){
	scaleX = ((float)_height / 320.0);
	scaleY = ((float)_width / 240.0);
}

void Map::renderSelected(){		
	mapHandler.setSrc(selected.getFactx(),selected.getFacty(),TILE_OPTION,TILE_OPTION);
	mapHandler.render(265, 202, TILE_SIZE, TILE_SIZE);	
}

void Map::renderMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
			Tile tile = opt.at((*it).getType());
			mapHandler.setSrc(tile.getFactx(),tile.getFacty(),TILE_OPTION,TILE_OPTION);
			mapHandler.render((*it).getX()+x, (*it).getY()+y, TILE_SIZE, TILE_SIZE);						
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
			if((type<=10)&& (type>default_tile)){
				type = TYPE_PLAYER;
			}
			Tile tile = Tile(TILE_SIZE*col,TILE_SIZE*fil,type,fil,col);						
			tileSet.push_back(tile);
		}
	}	
	//std::cout<<"pas2"<<std::endl;
}

void Map::updateClick(){
	int valx, valy;	
	SDL_GetMouseState(&valx,&valy);	
	xRelative = valx/scaleX;
	yRelative = valy/scaleY;
}

void Map::load_objectTiles(){		
	int typeKey = TYPE_KEY;
	int typePlayer = TYPE_PLAYER;
	int typeHeal = TYPE_HEAL;
	int typeAmmo = TYPE_AMMO;	
	int typeWeapon = TYPE_WAEPON;
	int typeTreasure = TYPE_TREASURE;
	int typeInmovable = TYPE_INMOVABLE;
	int typeDoor = TYPE_DOOR;
	int typeWall = TYPE_WALL;

	int type;
	int element = 0;	
	for (int fil = 0; fil < OPTION_ROW; ++fil){
		for (int col = 0; col < OPTION_COL; ++col){
			if(element == 0){
				type = 0;
			}if((element>0)&&(element<=11)){
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
				type = typePlayer;				
			}if((element >22)&&(element<=28)){
				type = typeInmovable;
				typeInmovable++;
			}if((element >28)&&(element<=32)){
				type = typeTreasure;
				typeTreasure++;
			}if((element >32)&&(element<=34)){
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
			}
    }			
}

void Map::putTileMap(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
		if((*it).existPosition(xRelative,yRelative,x,y)){
			int typeOri = selected.getType();
			int typeDest = (*it).getType();
			if((typeOri !=TYPE_PLAYER)&&(typeDest!=TYPE_PLAYER)){
				if(typeOri == typeDest){					
					(*it).setType(default_tile);
				}else{
					(*it).setType(typeOri);
				}
			}else if((typeOri ==TYPE_PLAYER)&&(typeDest!=TYPE_PLAYER)){
				if(playersPendings>0){
					playersPendings--;
					players++;
					(*it).setType(typeOri);									
			}
			}else if((typeOri!=TYPE_PLAYER)&&(typeDest==TYPE_PLAYER)){
				playersPendings++;
				players--;
				(*it).setType(typeOri);	
			} else if(typeOri == typeDest==TYPE_PLAYER){
				(*it).setType(default_tile);
				playersPendings++;
				players--;				
			}else {
				std::cout<<typeOri<<":"<<typeDest<<std::endl;				
				(*it).setType(typeOri);	
			}
		}	
	}	
	textPlayerHandler.setText(std::to_string(playersPendings));			
}

void Map::pollEvent(SDL_Event &evento){
	updateClick();
	
	if(evento.type == SDL_MOUSEBUTTONDOWN){
		if(evento.button.button == SDL_BUTTON_LEFT){									
			changeSelected();
			putTileMap();
		}
	}if ((evento.type == SDL_QUIT)|| 
		(evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE)){	
			if(playersPendings == 0){
				canExit = true;
				updateModel();
			}else{
				canExit = false;
			} 	
	}
}

bool Map::getCanExit() const{
	return canExit;
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
	int playersProcessed = 1;
	for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type =  getTypebyFilCol(fil,col);
			if((col == 0 ) || (col == columns -1) || 
				(fil == 0) || (fil == rows -1)){
					if((type < default_null_tile) || (type >= default_null_tile+11)){
						type = default_null_tile;
					}
				}
			if(type == TYPE_PLAYER){
				type = playersProcessed;
				playersProcessed++;
			}				
			map[fil][col] = type;			
		}
	}
}

void Map::setRenderer(SDL_Renderer *_renderer){
	winRenderer = _renderer;
	mapHandler.setRenderer(winRenderer);
	textPlayerHandler.setRenderer(winRenderer,yellow);	
}

void Map::createNewMap(int _rows, int _columns,int _maxplayer){
	players =0;
	playersPendings =_maxplayer;
	for (int fil = 0; fil < _rows; ++fil){
		std::vector<int> v1;
		for (int col = 0; col < _columns; ++col){
			v1.push_back(default_value);
		}
		map.push_back(v1);
	}
}

void Map::openfromfile(std::string _path,std::string &_file){		
	YAML::Node config = YAML::LoadFile(_path + "/" + _file + ".yaml");
	map = config["model"].as<std::vector<std::vector<int>>>();
	players = config["players"].as<int>();	
	playersPendings = 0;
	//std::cout<<"pase"<<std::endl;
}

void Map::init(Settings &set, std::string &_name,int _maxplayer,bool create){
	map.clear();	
	tileSet.clear();
	if(create){
		createNewMap(set.getRows(), set.getColumns(),_maxplayer);
	} else{
		openfromfile(set.getPath(),_name);
	}
	rows = map.size();
	columns = map[0].size();		
	name = _name;	
	textPlayerHandler.setText(std::to_string(playersPendings));		
	load();
}

std::vector<std::vector<int>> Map::getMap() const{
	return map;
}

Map::~Map(){}

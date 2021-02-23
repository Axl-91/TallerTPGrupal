#include "Map.h"
#include "Defines.h"

Map::Map():mapHandler(0, 0, 384, 384, "Media/MenuEditor/tiles.png"),
		  textPlayerHandler(" "){
	fillTypes();
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
}

void Map::updateClick(){
	int valx, valy;	
	SDL_GetMouseState(&valx,&valy);	
	xRelative = valx/scaleX;
	yRelative = valy/scaleY;
}

void Map::fillTypes(){
	types.insert({0,TYPE_NULL});	
	types.insert({1,TYPE_WALL_1});
	types.insert({2,TYPE_WALL_2});
	types.insert({3,TYPE_WALL_3});	
	types.insert({4,TYPE_WALL_4});
	types.insert({5,TYPE_WALL_5});
	types.insert({6,TYPE_WALL_6});
	types.insert({7,TYPE_WALL_7});
	types.insert({8,TYPE_WALL_8});
	types.insert({9,TYPE_WALL_9});
	types.insert({10,TYPE_WALL_10});
	types.insert({11,TYPE_WALL_11});
	types.insert({12,TYPE_DOOR_1});
	types.insert({13,TYPE_DOOR_2});
	types.insert({14,TYPE_DOOR_3});
	types.insert({15,TYPE_HEAL_1});
	types.insert({16,TYPE_HEAL_2});
	types.insert({17,TYPE_HEAL_3});
	types.insert({18,TYPE_WAEPON_1});
	types.insert({19,TYPE_WAEPON_2});
	types.insert({20,TYPE_WAEPON_3});
	types.insert({21,TYPE_AMMO});
	types.insert({22,TYPE_PLAYER});
	types.insert({23,TYPE_INMOVABLE_1});
	types.insert({24,TYPE_INMOVABLE_2});
	types.insert({25,TYPE_INMOVABLE_3});
	types.insert({26,TYPE_INMOVABLE_4});
	types.insert({27,TYPE_INMOVABLE_5});
	types.insert({28,TYPE_INMOVABLE_6});
	types.insert({29,TYPE_TREASURE_1});
	types.insert({30,TYPE_TREASURE_2});
	types.insert({31,TYPE_TREASURE_3});
	types.insert({32,TYPE_TREASURE_4});
	types.insert({33,TYPE_KEY_1});
	types.insert({34,TYPE_KEY_2});	
	types.insert({35,TYPE_KEY_2});
}

void Map::load_objectTiles(){			
	int type;
	int element = 0;	
	for (int fil = 0; fil < OPTION_ROW; ++fil){
		for (int col = 0; col < OPTION_COL; ++col){
			type = types.at(element);
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

int Map::getTypebyFilCol(int _fil, int _col) {
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    					
		if((*it).existbyFilCol(_fil,_col)){
			return (*it).getType();
		}
	}
	return TYPE_NULL;
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

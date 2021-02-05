#include "Map.h"

Map::Map():mapHandler(0, 0, 96, 33, "tiles.png")
{}

void Map::render(){
	for (std::vector<Tile>::iterator it = tileSet.begin() ; it != tileSet.end(); ++it){		    			
		//if(checkCollision( camera, (*it).getBox())){
			SDL_Rect clip = gTileClips[(*it).getType()];
			mapHandler.setSrc(clip.x,clip.y,clip.h,clip.w);
			mapHandler.render((*it).getX() - camera.x, (*it).getY()-camera.y, TILE_HEIGHT, TILE_WIDTH);				
		//}
	}	
	dot.render(camera);
}

void Map::load(){	
	for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type = map[fil][col];
			Tile tile = Tile(TILE_HEIGHT*col+x,TILE_WIDTH*fil+y,type);						
			tileSet.push_back(tile);
		}
	}
}

void Map::pollEvent(SDL_Event &evento){
	dot.pollEvent(evento);
	dot.move();
	dot.setCamera(camera);
}

void Map::init(Settings &set, SDL_Renderer* _renderer){	
	winRenderer = _renderer;
	mapHandler.setRenderer(winRenderer);
	map = set.getmap();
	rows = map.size();
	columns = map[0].size();		
	dot.init(winRenderer);
	load();		
	gTileClips[ TILE_1 ].x = 0;
	gTileClips[ TILE_1 ].y = 0;
	gTileClips[ TILE_1 ].w = TILE_WIDTH;
	gTileClips[ TILE_1 ].h = TILE_HEIGHT;

	gTileClips[ TILE_2 ].x = 0;
	gTileClips[ TILE_2 ].y = 16;
	gTileClips[ TILE_2 ].w = TILE_WIDTH;
	gTileClips[ TILE_2 ].h = TILE_HEIGHT;

	gTileClips[ TILE_3 ].x = 16;
	gTileClips[ TILE_3 ].y = 0;
	gTileClips[ TILE_3 ].w = TILE_WIDTH;
	gTileClips[ TILE_3 ].h = TILE_HEIGHT;
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

#include "Settings.h"
#include<fstream>
#include <iostream>

Settings::Settings(){
    config = YAML::LoadFile(filename);
}

void Settings::init(char* _mapname){     
    if(_mapname){
        std::string mapname(_mapname);
        const YAML::Node& nodes = config["maps"];

        for(YAML::const_iterator it=nodes.begin(); it!=nodes.end(); ++it){
            const YAML::Node& model = *it;    
            if(mapname == model["name"].as<std::string>()){
                maxPlayers = model["players"].as<int>();            
                map = model["model"].as<std::vector<std::vector<int>>>();
                rows = map.size();
                columns = map[0].size();
                found = true;
            }
            
         } 
    } if(found==false) {
        rows = config["rows"].as<int>();
        columns = config["col"].as<int>();
        for (int fil = 0; fil < rows; ++fil){
            std::vector<int> v1;
	    	for (int col = 0; col < columns; ++col){
                v1.push_back(default_value);
		    }
            map.push_back(v1);
	    }
    }

}

void Settings::list(){
    int rows = map.size();
	int columns = map[0].size();
    std::cout<<columns<<":"	<<rows<<std::endl;
    /*for (int fil = 0; fil < rows; ++fil){
		for (int col = 0; col < columns; ++col){
			int type = map[fil][col];
			Tile tile = Tile(TILE_SIZE*col,TILE_SIZE*fil,type,fil,col);						
			tileSet.push_back(tile);
		}
	}*/
}

void Settings::saveChanges(std::vector<std::vector<int>> _map){
    std::ofstream fout(filename);
    std::cout<<"aqui"<<_map[0][0];
    config["map"] = _map; 
    fout << config;
}
std::vector<std::vector<int>> Settings::getmap() const{
    return map;
}
int Settings::getmaxlayers() const{
    return maxPlayers;
}

Settings::~Settings(){}
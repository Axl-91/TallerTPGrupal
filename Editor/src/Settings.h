#ifndef __SETTINGS__
#define __SETTINGS__

#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include "yaml-cpp/yaml.h"

const int default_value = 0;
const int default_players = 3;

class Settings{
private:           
    int maxPlayers, rows, columns,count;
   
    std::string mapname;
    std::string filename = "nivel.yaml";
    std::string cfg = "config.yaml";
    std::string path;
   	std::vector<std::string> maps;
    std::vector<int> players;
    bool found = false;
public:
    Settings();    
    void UpdateFiles();
    int getColumns() const;
    int getRows() const;
    void init(std::string &_mapname);  
    std::vector<std::string> getMaps() const; 
    std::string getPath() const; 
    void saveChanges(std::vector<std::vector<int>>map,std::string _mapname);   
    int getmaxlayers() const;
    ~Settings();
};

#endif
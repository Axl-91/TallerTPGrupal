#include "Settings.h"
#include<fstream>
#include <iostream>

Settings::Settings(){}

void Settings::init(char* _filename){ 
    if((_filename != "") && (_filename != NULL)){
        std::string filename(_filename);
    }    
    config = YAML::LoadFile(filename);      
    resolutionWidth = config["resolutionWidth"].as<int>();
    resolutionHeigh = config["resolutionHeigh"].as<int>();    
    maxPlayers = config["maxPlayers"].as<int>();   
    resolutionsWidthOP = config["resolutionsWidthOP"].as<std::vector<int>>();   
    resolutionsHeighOP = config["resolutionsHeighOP"].as<std::vector<int>>();   
    maxplayersOP = config["maxplayersOP"].as<std::vector<int>>();       
    map = config["map"].as<std::vector<std::vector<int>>>();    
}

void Settings::saveChanges(){
    std::ofstream fout(filename);
    config["map"] = map; 
    fout << config;
}

int Settings::getresW() const{
    return resolutionWidth;
}

std::vector<int> Settings::getresolutionsWidthOP() const{
    return resolutionsWidthOP;
}

std::vector<int> Settings::getresolutionsHeighOP() const{
    return resolutionsHeighOP;
}
std::vector<int> Settings::getmaxplayersOP() const{
    return maxplayersOP;
}

std::vector<std::vector<int>> Settings::getmap() const{
    return map;
}

int Settings::getresH() const{
    return resolutionHeigh;
}
int Settings::getmaxlayers() const{
    return maxPlayers;
}

Settings::~Settings(){}
#include "Settings.h"
#include<fstream>
#include <iostream>

Settings::Settings(){
    config = YAML::LoadFile(filename);      
    resW = config["resW"].as<int>();
    resH = config["resH"].as<int>();
    minplayers = config["minplayers"].as<int>();
    maxplayers = config["maxplayers"].as<int>();         
    std::vector<std::vector<int>> lvl1 = config["map"].as<std::vector<std::vector<int>>>();
}

void Settings::init(char* _filename){ 
    if((_filename != "") && (_filename != NULL)){
        std::string filename(_filename);
    }    
    config = YAML::LoadFile(filename);      
    resW = config["resW"].as<int>();
    resH = config["resH"].as<int>();
    minplayers = config["minplayers"].as<int>();
    maxplayers = config["maxplayers"].as<int>();         
    std::vector<std::vector<int>> lvl1 = config["map"].as<std::vector<std::vector<int>>>();    
}

void Settings::saveChanges(){
    std::ofstream fout(filename);    
    fout << config;
}

int Settings::getresW() const{
    return resW;
}

int Settings::getresH() const{
    return resH;
}
int Settings::getmaxlayers() const{
    return maxplayers;
}
int Settings::getminplayers() const{
    return minplayers;
}

Settings::~Settings(){}
#include "Settings.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


Settings::Settings(){
    YAML::Node config = YAML::LoadFile(cfg);
    count = config["count"].as<int>();
    rows = config["rows"].as<int>();
    columns = config["columns"].as<int>();
    path = config["path"].as<std::string>();
    players = config["players"].as<std::vector<int>>();
    UpdateFiles();
}

void Settings::init(std::string &_mapname){ 
    if(_mapname ==""){
        _mapname = "map" + std::to_string(count);
    }
}

void Settings::UpdateFiles(){
    maps.clear();
    for (const auto & entry : fs::directory_iterator(path)){
        std::string file = entry.path().filename().string();
        std::string token = file.substr(0,file.find("."));
        maps.push_back(token);
    }
}

void Settings::saveChanges(std::vector<std::vector<int>> _map,std::string _mapname){
    mapname = _mapname;
    YAML::Emitter out;
    YAML::Node doc;
    doc["players"] = 3;
    doc["model"] = _map;    
    doc.SetStyle(YAML::EmitterStyle::Flow);    
    std::ofstream fout(path + "/" + mapname + ".yaml");
    out << doc;
    fout << out.c_str();
}

int Settings::getmaxlayers() const{
    return maxPlayers;
}

int Settings::getRows() const{
    return rows;
}

int Settings::getColumns() const{
    return columns;
}
std::string Settings::getPath() const{
    return path;
}

std::vector<std::string>  Settings::getMaps() const{
    return maps;
}

Settings::~Settings(){}
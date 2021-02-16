#ifndef __SETTINGS__
#define __SETTINGS__

#include <iostream>
#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"

const int default_value = 0;

class Settings{
private:
    YAML::Node config;        
    int maxPlayers, rows, columns;
    std::vector<std::vector<int>> map;
    std::string mapname;
    std::string filename = "nivel.yaml";
    bool found = false;
public:
    Settings();
    void list();
    void init(char* _map);
    void close();
    void saveChanges(std::vector<std::vector<int>>map);   
    int getmaxlayers() const;
    std::vector<int> getresolutionsWidthOP() const;
    std::vector<int> getresolutionsHeighOP() const;
    std::vector<int> getmaxplayersOP() const;  
    std::vector<std::vector<int>> getmap() const;  
    ~Settings();
};

#endif
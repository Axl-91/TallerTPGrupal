#ifndef __SETTINGS__
#define __SETTINGS__

#include <iostream>
#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"

class Settings{
private:
    YAML::Node config;
    std::string filename = "nivel.yaml";
    int resolutionWidth; 
    int resolutionHeigh;
    int maxPlayers;
    std::vector<int> resolutionsWidthOP;
    std::vector<int> resolutionsHeighOP;
    std::vector<int> maxplayersOP;
    std::vector<std::vector<int>> map;
public:
    Settings();
    void init(char* _filename);
    void close();
    void saveChanges();
    int getresW() const;    
    int getresH() const;    
    int getminplayers() const;    
    int getmaxlayers() const;
    std::vector<int> getresolutionsWidthOP() const;
    std::vector<int> getresolutionsHeighOP() const;
    std::vector<int> getmaxplayersOP() const;    
    ~Settings();
};

#endif
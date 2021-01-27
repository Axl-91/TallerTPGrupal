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
    int resW; 
    int resH;
    int minplayers;
    int maxplayers;
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
    ~Settings();
};

#endif
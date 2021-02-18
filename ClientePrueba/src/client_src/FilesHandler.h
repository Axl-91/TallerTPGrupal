#ifndef __FILES_HANDLER__
#define __FILES_HANDLER__

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

class FilesHandler{
private:
    std::ifstream streamFiles;
    std::vector<std::string> vectorFiles;
    void createVectorFiles();
public:
    FilesHandler(std::string nameFile);
    std::vector<std::string> getVectorFiles();
    ~FilesHandler();
};

#endif

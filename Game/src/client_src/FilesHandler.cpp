#include "FilesHandler.h"

FilesHandler::FilesHandler(const std::string &nameString){
    streamFiles.open(nameString);
    createVectorFiles();
}

void FilesHandler::createVectorFiles(){
    while (!streamFiles.eof()){
        std::string stringFile;
        std::getline(streamFiles, stringFile, '\n');
        vectorFiles.push_back(stringFile);
    }
}

std::vector<std::string> FilesHandler::getVectorFiles(){
    return vectorFiles;
}

FilesHandler::~FilesHandler(){
    streamFiles.close();
}

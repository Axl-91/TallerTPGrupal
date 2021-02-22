#include "FilesHandler.h"

FilesHandler::FilesHandler(const std::string &nameString){
    streamFiles.open(nameString);
    createVectorFiles();
}

void FilesHandler::createVectorFiles(){
    while (true){
        std::string stringFile;
        std::getline(streamFiles, stringFile);
        if (streamFiles.eof()){
            return;
        }
        vectorFiles.push_back(stringFile);
    }
}

std::vector<std::string> FilesHandler::getVectorFiles(){
    return vectorFiles;
}

FilesHandler::~FilesHandler(){
    streamFiles.close();
}

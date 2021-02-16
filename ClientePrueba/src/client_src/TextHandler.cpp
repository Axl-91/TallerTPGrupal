#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "TextHandler.h"

TextHandler::TextHandler(std::string text){
    vectorText = {text};
}

TextHandler::TextHandler(std::vector<std::string> &texts): vectorText(texts){}

void TextHandler::destroyTextures(){
    for(size_t i=0; i<vectorTextures.size(); i++){
         SDL_DestroyTexture(vectorTextures[i]);
    }
    vectorText.clear();
    vectorTextures.clear();
}

void TextHandler::setRenderer(SDL_Renderer* renderer, SDL_Color color){
    rendererWin = renderer;
    colorText = color;
    getTextures(renderer, color);

}

void TextHandler::getTextures(SDL_Renderer* renderer, SDL_Color color){
    SDL_Surface* surfaceText;
	TTF_Font* font = TTF_OpenFont("Media/Menu/DejaVuSans-Bold.ttf", 14);

    for(size_t i=0; i<vectorText.size(); i++){
        surfaceText = TTF_RenderText_Blended(font, vectorText[i].c_str(), color);
        if (!surfaceText) {
            SDL_FreeSurface(surfaceText);
            throw std::exception();
        }
        vectorTextures.push_back(SDL_CreateTextureFromSurface(renderer, surfaceText));
        if (!vectorTextures.back()) {
            SDL_FreeSurface(surfaceText);
            throw std::exception();
        }
        SDL_FreeSurface(surfaceText);
    }
}

void TextHandler::render(int posX, int posY, int length, int height, int pos){
    SDL_Rect rect = {posX, posY, length, height};
    SDL_RenderCopy(rendererWin, vectorTextures[pos], NULL, &rect);
}

void TextHandler::render(int posX, int posY, int length, int height){
    SDL_Rect rect = {posX, posY, length, height};
    SDL_RenderCopy(rendererWin, vectorTextures[0], NULL, &rect);
}

void TextHandler::setText(std::string newText){
    destroyTextures();
    vectorText.push_back(newText);
    getTextures(rendererWin, colorText);
}

TextHandler::~TextHandler(){
    destroyTextures();
}

#include "Dot.h"

Dot::Dot():mapDot(0, 0, 20, 20, "dot.bmp"){}

void Dot::init(SDL_Renderer* _renderer){ 
    //winRenderer = _renderer;
    mBox.x = 15;
    mBox.y = 75;   
    mVelX = 0;
    mVelY = 0;
    mapDot.setRenderer(_renderer);
}

void Dot::render(SDL_Rect& camera){	
    mapDot.render(mBox.x - camera.x, mBox.y - camera.y, DOT_HEIGHT, DOT_WIDTH);      
    //std::cout<< mBox.x << "-" << camera.x << std::endl; 
}

void Dot::pollEvent(SDL_Event &e){   
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

Dot::~Dot(){
	//close();
}

void Dot::move(){
    mBox.x += mVelX;    
    if((mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > 1280 )) {        
        mBox.x -= mVelX;
    }

    mBox.y += mVelY;
    if(( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > 960 )) {        
        mBox.y -= mVelY;
    }
}

void Dot::setCamera(SDL_Rect& camera ){
    camera.x = ( mBox.x + DOT_WIDTH/2)- 320; 
	camera.y = ( mBox.y + DOT_HEIGHT/2)- 240;

	if( camera.x < 0 ){ 
		camera.x = 0;
	}
	if( camera.y < 0 ){
		camera.y = 0;
	}
	if( camera.x > 1280 - camera.w )	{
		camera.x = 1280 - camera.w;
	}
	if(camera.y > 960 - camera.h ){
		camera.y = 960 - camera.h;
	}
}



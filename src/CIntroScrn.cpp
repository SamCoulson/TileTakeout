#include "../include/CIntroScrn.h"

CIntroScrn::CIntroScrn( CSDLGraphics& graphics, CGlobalGameData& globalGameData )
	: IScreen( graphics ){

	this->graphics = &graphics;
	titleScreen = NULL;
}	

bool CIntroScrn::init(){

	//scrnEntityManager.AddEntity("TitleScreen.png", pTitlescrn, 0, 0);
	titleScreen = graphics->loadImageFromFile( "./images/TitleScreen.png", 255, 0, 255 );

	quit = false;

	return true;
}

void CIntroScrn::update(){

}

void CIntroScrn::render(){

	graphics->clearScreen(0, 0, 0);

	graphics->draw(0, 0, titleScreen, SDL_GetVideoSurface(), NULL );

	graphics->update();
	//g_pRender->ClearScreen( 0, 0, 0);
	//scrnEntityManager.UpdateEntities();
}

void CIntroScrn::processEvents( SDL_Event* event )
{
	if(event->key.type == SDL_KEYDOWN)
	{
		switch( event->key.keysym.sym )
		{
		case SDLK_RETURN:
			quit = true;				
			break;
		case SDLK_ESCAPE:
			quit = true;
			break;
		default:
			break;
		}
	}

	if( event->type == SDL_QUIT)
	{
		quit = true;
	}
}


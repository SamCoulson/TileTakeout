#ifndef H_INTROSCRN_INC
#define H_INTROSCRN_INC

#include "../include/CSDLGraphics.h"
#include "../include/IScreen.h"

class CIntroScrn : public IScreen{

public:
	CIntroScrn( CSDLGraphics&, CGlobalGameData& );
	~CIntroScrn(){};

	virtual bool init();
	virtual void update();
	virtual void render();
    	virtual void cleanUp(){};
	virtual void processEvents( SDL_Event* );
	virtual bool requestQuit(){ return quit; }
	virtual bool isPaused(){ return false; }
		
private:
	CSDLGraphics *graphics;
	SDL_Surface *titleScreen;

	bool quit;

};

#endif // H_INTROSCRN_INC

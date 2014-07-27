#include "../include/main.h"
#include <vector>

using namespace std;

int main( int argc, char* args[])
{
	//CScreenManager scrnManager;

	//CTimer timer;

	bool run_app;
	bool m_paused; 

	SDL_Event event;

	CGlobalGameData* globalGameData = new CGlobalGameData();

	// Create SDL objects
	CSDLGraphics* graphics = new CSDLGraphics(); 

	// Intialise SDL, setup subsystems
	if(!graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, 24, SDL_SWSURFACE, "Breakout Clone" ))
	{
		cout << "Could not initialise CSDLGraphics object" << endl ;
		return false;
	}
		
	// Intro screen object
	IScreen *introScrn = new CIntroScrn( *graphics, *globalGameData );

	// Main game screen object
	IScreen *gameScrn = new CGame( *graphics, *globalGameData );

	// High score screen
//	CHighScoreScrn g_HighScoreScrn;
	// Score entry box
//	CScoreEntry g_ScoreEntry;
/*	
	// Register the screen for management
	scrnManager.RegisterScreen( g_Intro, 0);
	scrnManager.RegisterScreen( g_Game, 1);
	scrnManager.RegisterScreen( g_HighScoreScrn, 2);
	scrnManager.RegisterScreen( g_ScoreEntry, 3 );

	scrnManager.ChangeScreen( 0 );
*/
	vector< IScreen* > screens;
	screens.push_back( introScrn );
	screens.push_back( gameScrn );

	vector< IScreen* >::iterator it = screens.begin();
	IScreen* currentScreen = (*it);

	run_app = true;

	bool isInitialised = false;

	Uint32 start_time, end_time = 0;
	
	//Game needs a global event handler to handle paused state 
	while(run_app != false)
	{
		// Are there any events waiting to be proccessed 
		SDL_PollEvent(&event);

		// Process input
		//Handle_Input();

		// Record time at begining of frame
		start_time = SDL_GetTicks();
		
		// The the screen has not been initialised then load it up.
		if( isInitialised == false ){
			if( currentScreen->init() == false ){
				cout << "Failed to initialise screen!" << endl;
				run_app = false;
			}	
			isInitialised = true;	
		}

		currentScreen->processEvents( &event );
		currentScreen->update();
		currentScreen->render();
	
		// If the loop is still inside of the allotted time, in ms, per frame
		if( (SDL_GetTicks() - start_time) < 1000 / FRAMES_PER_SECOND ) 
		{
			// Work out what the time should be once the frame has finished
			end_time = start_time + 1000 / FRAMES_PER_SECOND;
			// Work out how long is left given how long the frame actually took to how long it should take.
			// Sleep for the reamiander of the frame.
			SDL_Delay( end_time - SDL_GetTicks() );
		}

		// On a screen quitting check what conditions it quits under
		if( ( currentScreen->requestQuit() ) && ( event.key.keysym.sym == SDLK_ESCAPE ) ){
			run_app = false;
		}else if( currentScreen->requestQuit() ){
			// Progress vector pointer to next screen
			++it;

			// If last screen go back to intro screen
			if( it == screens.end() ){
				it = screens.begin();
			}

			// Make current screen the screen pointed to in vector
			currentScreen = (*it);

			// Make sure screen is initialised or re-initialised
			isInitialised = false;	
		}
	}

	return 0;
}



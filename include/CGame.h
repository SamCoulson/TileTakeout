#ifndef INC_GAME_H
#define INC_GAME_H

#include "IScreen.h"
//#include "CScreenManager.h"
#include "CSprite.h"
#include "CGrid.h"
#include "CCollision.h"
//#include "CTimer.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_GAMEAREA_WIDTH (SCREEN_WIDTH-40)
#define MIN_GAMEAREA_WIDTH 40
#define MAX_GAMEAREA_HEIGHT (SCREEN_HEIGHT-40)
#define MIN_GAMEAREA_HEIGHT 40

#define LEFT_EDGE 1
#define RIGHT_EDGE 2
#define TOP_EDGE 3
#define BOTTOM_EDGE 4

class CGame : public IScreen{

public:
	// Constructor
	CGame( CSDLGraphics&, CGlobalGameData& );
	// Deconstructor
	~CGame(){};

	// Initialisation code for all objects and global data
	virtual bool init();
	virtual void render();
	virtual void update();
	virtual void cleanUp();
	virtual void processEvents( SDL_Event* );
	virtual bool requestQuit();
	virtual bool isPaused(){};

private:

	// Movable objects global pointers 
	SDL_Surface* ball;
	SDL_Surface* bat;

	// Static object global pointers
	SDL_Surface *bkGround;
	SDL_Surface *arenaFrame;

	SDL_Surface* yellowBlock;
	SDL_Surface* blueBlock;
	SDL_Surface* greenBlock;

//	CSprite *pPause;

	CGrid *blocks;

	// Timer for displaying text for a duration
//	CTimer *pText_timer;

	// Pointer to collision object for collision detection functions
	CCollision *collider;

	// Track ball speed
	int ball_speed;
	int bat_speed;

	// Score variables
	unsigned int m_score;
//	stringstream score;

	// Track level number
	unsigned int levelNo;

	// Used by IsGameRunning to signal when the user presses escape or x'ed out.
	bool m_QuitGame;

	// Used by IsPaused() whe user pauses the game
	bool m_paused;


	bool m_isLevelActive;

	bool m_showIntroText;

	// Track if level has been started used for start of level text
	bool m_isLevelStarted;

	// Counter to track number of blocks left
	unsigned int m_totalNoBlocks;

	// Track if player has launched the ball
	bool m_ballReleased;

	// Lives counter
	int m_lives;
//	stringstream lives;

	// Hold information on grid blocks used for collision detection
//	Rect current_block;

	// Hold data on bat and ball metrics used for collision detection
	SDL_Rect ball_rect;
	int ball_vel_x;
	int ball_vel_y;

	SDL_Rect bat_rect;
	int bat_vel_x;

	// Stores all levels as continious strings
	std::vector<std::string> levels;

	// Functions
	void deflect(unsigned int side, int* velX, int* velY );
	
	
	bool LoadLevelFromFile( std::string levelDataFile );

	bool setLevel( unsigned int LevelNo );

	//void Handle_Input();

	void UpdateScore( unsigned int );
	void UpdateLives(); // May need to recode to for addition of lives

	CSDLGraphics *graphics;

};

#endif // INC_GAME_H

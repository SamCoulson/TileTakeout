#ifndef INC_MAIN_H
#define INC_MAIN_H

#include "../../gamelibrary/include/CSDLGraphics.h"
#include "CGame.h"
#include "CIntroScrn.h"
//#include "CHighScoreScrn.h"
//#include "CScoreEntry.h"
//#include "CCollision.h"
//#include "CTimer.h"

#include <tchar.h>
#include <iostream>
#include <sstream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAMES_PER_SECOND 30

// used for collision detection
#define NO_COLLIDE 0
#define RIGHT_SIDE 1
#define LEFT_SIDE 2
#define TOP_SIDE 3
#define BOTTOM_SIDE 4

// void MoveBat();

#endif // INC_MAIN_H

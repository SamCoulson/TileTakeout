#ifndef INC_COLLISION_H
#define INC_COLLISION_H

//#include "Globals.h"
#include "stdlib.h"
#include "CSDLGraphics.h"

enum {
	TOP_EDGE = 1,
	BOTTOM_EDGE = 2,
	LEFT_EDGE = 3,
	RIGHT_EDGE = 4,
	CORNER = 5
};

class CCollision{

public:
	CCollision(){};
	~CCollision(){};
	// Subtraction collison detection
	bool CheckCollide(SDL_Rect &entity1, SDL_Rect &entity2);

	// Returns collisoin edge with SAT with velocity collision
	// Assumes entity2 to be static

	int CollisionEdge( SDL_Rect &entity1, SDL_Rect &entity2); 
	
	//int CheckCollideAABB(Rect &entity1, Rect &entity2);

	bool IsIntersect(int x, int y, SDL_Rect &rect);

private:


};

#endif // INC_COLLISION_H

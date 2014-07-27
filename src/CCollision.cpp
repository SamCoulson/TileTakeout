#include "../include/CCollision.h"

// Basic box based collision detection
bool CCollision::CheckCollide( SDL_Rect &entity1, SDL_Rect &entity2){

	// Taken in part from Lazy Foo

	// First work out points which define the corners side of each entities A and B.
	int leftA = entity1.x;
	int rightA = entity1.x + entity1.w;
	int topA = entity1.y;
	int bottomA = entity1.y + entity1.h;

	int leftB = entity2.x;
	int rightB = entity2.x + entity2.w;
	int topB = entity2.y;
	int bottomB = entity2.y + entity2.h;

	// Does bottom of entity1 overlap top of entity 2
	if(bottomA < topB)
	{
		return false;
	}

	// Does top of entity1 overlap bottom of entity 2
	if(topA > bottomB)
	{
		return false;
	}

	// Does the right hand side of entity1 overlap left hand side of entity2
	if(rightA < leftB)
	{
		return false;
	}

	// Does the left hand side of entity1 overlap the right hand side of entity2
	if(leftA > rightB)
	{
		return false;
	}

	// If not collisons detected return true
	return true;

}
/*
// Returns which edge of entity2, entity1 collided with. Entity2 must always be the static entity.
int CCollision::CollisionEdge(Rect &entity1, Rect &entity2)
{
	// Centre points or half-widths for both rectangles
	int ent1Xcentre = 0, ent1Ycentre = 0, ent2Xcentre = 0, ent2Ycentre = 0;

	ent1Xcentre = entity1.w / 2;
	ent1Ycentre = entity1.h / 2;

	ent2Xcentre = entity2.w / 2;
	ent2Ycentre = entity2.h / 2;

	// Threshold for collison between both rectangles
	UINT thresholdX, thresholdY = 0;

	// Add the two half widths together to work out the minimum distance before an overlapp occurs.
	thresholdX = ent1Xcentre + ent2Xcentre;
	thresholdY = ent1Ycentre + ent2Ycentre;

	// Calculate distance between the centres of both objects on the X and Y axis
	UINT distOnXaxis = abs(((int)entity2.x + ent2Xcentre) - ((int)entity1.x + ent1Xcentre));
	UINT distOnYaxis = abs(((int)entity2.y + ent2Ycentre) - ((int)entity1.y + ent1Ycentre));

	// Id there overlap on X-axis and Y-axis 
	if( distOnXaxis  <= thresholdX  && 
		distOnYaxis  <= thresholdY ) 
	{
		// If the distance between the centres on the X-axis is greater than on the Y then do A-axis test for edge
		if( distOnXaxis > distOnYaxis )
		{
			// Which side of centre of entity2 is entity1 on the X-axis
			if( (entity1.x + ent1Xcentre) > (entity2.x + ent2Xcentre) )
			{
				return RIGHT_EDGE;
			}
			else
			{
				return LEFT_EDGE;
			}
		}
		else // Else do Y-axis test
		{
			// Which side of centre of entity2 is entity1 on the Y-axis
			if( (entity1.y + ent1Ycentre) > (entity2.y + ent2Ycentre) )
			{
				return BOTTOM_EDGE;
			}
			else
			{
				return TOP_EDGE;
			}
		}
	}

	return 0;
}
*/
// Checks for intersect on each corner of the rectangle if true then works out which edge is colliding and returns this.
int CCollision::CollisionEdge( SDL_Rect &entity1, SDL_Rect &entity2)
{
	int leftA = entity1.x;
	int rightA = entity1.x + entity1.w;
	int topA = entity1.y;
	int bottomA = entity1.y + entity1.h;

	int leftB = entity2.x;
	int rightB = entity2.x + entity2.w;
	int topB = entity2.y;
	int bottomB = entity2.y + entity2.h;

	if( IsIntersect( entity1.x, entity1.y, entity2) )
	{
		// Left top corner
		if( (abs(leftA - rightB)) > abs(bottomB - topA) )
		{
			return BOTTOM_EDGE;
		}
		else
		{
			return RIGHT_EDGE;
		}
		
	}
	
	if( IsIntersect( (entity1.x + entity1.w), entity1.y, entity2) )
	{
		// Right top corner
		if( (rightA - leftB) > (bottomB - topA) )
		{
			return BOTTOM_EDGE;
		}
		else
		{
			return LEFT_EDGE;
		}
	}

	if( IsIntersect( entity1.x, entity1.y + entity1.h, entity2) )
	{
		// Left bottom corner
		if( (abs(leftA - rightB)) > (bottomA - topB) )
		{
			return TOP_EDGE;
		}
		else
		{
			return RIGHT_EDGE;
		}
	}

	if( IsIntersect( (entity1.x + entity1.w), (entity1.y + entity1.h), entity2) )
	{
		// Right bottom corner
		if( (rightA - leftB) > (bottomA - topB) )
		{
			return TOP_EDGE;
		}
		else
		{
			return LEFT_EDGE;
		}
	}

	return 0;
}

bool CCollision::IsIntersect(int x, int y, SDL_Rect &rect)
{
	if( (x >= rect.x) && (x <= rect.x + rect.w) && (y >= rect.y) && (y <= rect.y + rect.h) )
	{
		return true;
	}

	return false;
}

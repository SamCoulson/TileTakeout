#ifndef INC_CSPRITE_H
#define INC_CSPRITE_H

//#include "Globals.h"

enum DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN
	};

class CSprite
{
public:
	CSprite(){m_screenX = 0, m_screenY = 0, m_width = 0, m_height = 0, m_velX = 0, m_velY = 0, m_imageID = 0, isActive = true; }
	~CSprite(){};

	// *need to reconsider how this works* can have Move( DIRECTION ), or MoveLeft(), MoveRight() etc..
	// or have Move(Direction, velocity) if velocity is 0 then use currently set internal velocity
	void Move(int direction);
	void Move();

	// Get / Set imageID of entity for rendering
	int GetID() { return m_imageID; } const
	void SetID( uint8_t ID) { m_imageID = ID; }  

	// Determines if sprite should be drawn, true by default
	bool IsActive(){ return isActive; } const
	
	// Activate/Deactivate sprite for render
	void SetVisible( bool status){ isActive = status; }

	// Returns the width and height of the sprite 
	unsigned int GetWidth() { return m_width; } const
	unsigned int GetHeight() { return m_height; } const

	// Set the width and height of the sprite
	void SetWidth( int width) { m_width = width; }
	void SetHeight( int height) { m_height = height; }

	// Set position of sprite on screen
	bool SetX( unsigned int );
	bool SetY( unsigned int );

	// Return the position of the sprite on screen *Must be int type to allow for offscreen values i.e is ball less than 0, on collided detect*
	int GetX(){ return m_screenX; } 
	int GetY(){ return m_screenY; } 

	// Set velocity of sprite *mayebe these should just assert in instead of being abel to be tested * 
	bool SetVelX( int velX){ m_velX = velX; return true; }
	bool SetVelY( int velY){ m_velY = velY; return true; }

	// Return the sprite velocity
	int GetVelX(){ return m_velX; } 
	int GetVelY(){ return m_velY; } 

protected:

	// Sprite data

	// Sprite positions on screen 
	unsigned int m_screenX, m_screenY;

	// Sprite width and height used for collision information
	unsigned int m_width, m_height;

	// Velocity
	int m_velX, m_velY;

	// ID used to identify the sprite in the render image list
	unsigned int m_imageID;

	// Active flag used for render
	bool isActive;

	// Source clipping info used for sprite sheets
	//Rect srcimgclip;

	bool IsClipped;

};

#endif // INC_CSPRITE_H

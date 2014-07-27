#include "CSprite.h"
#include <iostream>

using namespace std;

bool CSprite::SetX( unsigned int pos_x ){


	// Not sure i should be doing bounds checking here
	if(pos_x < 0 || pos_x > 640 )
	{
		cout << "Invalid sprite coordinates passed to CSprite::Move" << endl;
		m_screenX = 0;
	}
	else
	{
		m_screenX = pos_x;
	}

	return true;
}

bool CSprite::SetY( unsigned int pos_y ){

	if(pos_y < 0 || pos_y > 480 )
	{
		cout << "Invalid sprite coordinates passed to CSprite::Move" << endl;
		m_screenY = 0;
	}
	else
	{
		m_screenY = pos_y;
	}

	return true;
}

// Move by velocity given a direction
void CSprite::Move(int direction)
{
	switch( direction )
	{
	case LEFT:
			m_screenX -= m_velX;
		break;
	case RIGHT:
			m_screenX += m_velX;
		break;
	case UP:
			m_screenY -= m_velY;
		break;
	case DOWN:
			m_screenY += m_velY;
		break;
	default:
		break;
	}
}

// Move given velocity values
void CSprite::Move()
{
	m_screenX += m_velX;
	m_screenY += m_velY;
}



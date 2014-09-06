#ifndef INC_SCORE_H
#define INC_SCORE_H

#include "GlobalGameData.h"

class CScoreEntry : public CScreenBase
{
public:
	CScoreEntry(){};
	~CScoreEntry(){};

	virtual bool Init();
	virtual void Update();
	virtual void Render();
    virtual void CleanUp();
	virtual void HandleEvents( SDL_Event& );
	virtual bool RequestQuit(){ return false;}

protected:

	CSprite* pScoreEntryBorder;

	// String to hold the user name
	string userName;

private:

};


#endif INC_SCORE_H

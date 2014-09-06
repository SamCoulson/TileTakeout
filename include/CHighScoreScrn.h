#ifndef H_HIGHSCORESCRN_INC
#define H_HIGHSCORESCRN_INC

#include "GlobalGameData.h"

class CHighScoreScrn : public CScreenBase
{
public:
	CHighScoreScrn(){ IsHighScore = false; IsNameEntered = false; }
	~CHighScoreScrn(){};

	virtual bool Init();
	virtual void Update();
	virtual void Render();
	virtual void CleanUp(){};
	virtual void HandleEvents( SDL_Event& );
	virtual bool RequestQuit();

private:

	typedef struct _SCOREDATA
	{
		string scorename;
		int score;
	}scoredata;

	scoredata topScore;

	vector< scoredata > topScores;

	void LoadTopScoresFromFile();

	// Sorting predicate function used in sort, note: function must be static
	static bool scorecmp( const scoredata& left, const scoredata& right );

	// Inserts a new high score in to the list
	void InsertNewHighScore( vector< scoredata >&, const int&, string& );

	CSprite* pHighScoreScrn;

	bool IsHighScore;
	bool IsNameEntered;
	bool m_QuitGame;
};

#endif H_HIGHSCORESCRN_INC

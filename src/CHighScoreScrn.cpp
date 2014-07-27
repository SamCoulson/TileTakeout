#include "CHighScoreScrn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


bool CHighScoreScrn::Init()
{
	// Add the score frame to render
	scrnEntityManager.AddEntity("HighScoreScrnBK.png", pHighScoreScrn, 0 ,40);

	// Load in the saved top scores
	LoadTopScoresFromFile();

	return true;
}

void CHighScoreScrn::Update()
{
	// Set flag that a new score has been reached
	if( IsHighScore == true)
	{
	// Insert the new score
	InsertNewHighScore( topScores, g_topscore, g_playername);
	// Set to false so that the names are not continiously sorted
	IsHighScore = false;
	}

	if( IsNameEntered == false)
	{
		// Comapare the bottom score with the current score
		if( topScores.back().score < g_topscore )
		{
			// Prompt user for their name
			scrnManager->PushScreen( 3 );
			
		}
		// Set to true so that the prompt does not reappear 
		IsNameEntered = true;
		IsHighScore = true;
		
	}
}

void CHighScoreScrn::Render()
{
	int columnSpacing = 80;

	vector< scoredata >::iterator it;

	std::ostringstream scoreAsString;

	g_pRender->ClearScreen( 0, 0, 0);

	scrnEntityManager.UpdateEntities();

	g_pRender->RenderText("Top Scores", 240, 50, 255, 0, 0);

	for(it = topScores.begin(); it < topScores.end(); it++ )
	{
		// Draw test for names
		g_pRender->RenderText("1.", 240, columnSpacing, 100, 100, 50 );
		g_pRender->RenderText((*it).scorename, 270, columnSpacing, 100, 100, 50 );
		scoreAsString << (*it).score;
		string scoreString( scoreAsString.str() );
		g_pRender->RenderText(scoreString, 320, columnSpacing, 100, 100, 50 );
		scoreAsString.str("");
		columnSpacing += 30;
	}
	
}

void CHighScoreScrn::HandleEvents( SDL_Event& event )
{	
	if(event.key.type == SDL_KEYDOWN)
	{
		switch( event.key.keysym.sym )
		{
		case SDLK_RETURN :
			scrnManager->ChangeScreen( 0 );
			break;
		case SDLK_ESCAPE :
			m_QuitGame = true;
			break;
		default:
			break;
		}
		event.key.type = SDL_KEYUP;
	}
	
	if( event.type == SDL_QUIT)
	{
		m_QuitGame = true;
	}
}

bool CHighScoreScrn::RequestQuit()
{
	if( m_QuitGame == true )
	{
		return true;
	}
	return false;
}

void CHighScoreScrn::LoadTopScoresFromFile()
{
	int scoreIndex, currentScore = 0;
	int sortIndex = 0;

	// top score file object Open file for input and output access
	fstream topscorefile("TopScore.txt");

	// Is file valid
	if(!topscorefile)
	{
		cout << "Could not open top score file" << endl;
	}

	// Read in 10 scores from file
	for(scoreIndex = 0; scoreIndex < 10; scoreIndex++)
	{
		topscorefile >> topScore.scorename >> topScore.score;
		topScores.push_back( topScore );
	}

	// Sort them in ascending order with the higher score to the lowest.
	std::sort( topScores.begin(), topScores.end(), scorecmp );
}

bool CHighScoreScrn::scorecmp( const scoredata& left, const scoredata& right )
{
	return left.score > right.score;
}


void CHighScoreScrn::InsertNewHighScore( vector< scoredata >& topScoreList, const int& newScore, string& playername )
{
	vector< scoredata >::iterator it;

	scoredata newEntry;

	newEntry.score = newScore;
	newEntry.scorename = playername;
	
	// Remove last entry on the list even if it is equal to the new score
	topScoreList.pop_back();
	/*
	for(it = topScoreList.begin(); it < topScoreList.end(); it++)
	{
		if( newScore > (*it).score )
		{
			topScoreList.insert( it, newEntry);
			it = topScoreList.end();
			//continue;
		}
		
	}
	*/
	// Push new score and sort 
	topScoreList.push_back( newEntry );
	// Sort them in ascending order with the higher score to the lowest.
	std::sort( topScores.begin(), topScores.end(), scorecmp );
	
}
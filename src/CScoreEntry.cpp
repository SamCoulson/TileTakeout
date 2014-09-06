#include "CScoreEntry.h"

string g_playername;

bool CScoreEntry::Init()
{
	scrnEntityManager.AddEntity("ScoreEntryBorder.png", pScoreEntryBorder, 215, 200);

	return true;
}

void CScoreEntry::Update()
{
	// If done flag is checked pop this state
}

void CScoreEntry::Render()
{
	scrnEntityManager.UpdateEntities();
	g_pRender->RenderText("Enter name", (pScoreEntryBorder->GetX() + 30), (pScoreEntryBorder->GetY()), 255, 100,  0 );

	// Render current state of name buffer
	g_pRender->RenderText(userName.c_str(), (pScoreEntryBorder->GetX() + 30), (pScoreEntryBorder->GetY() + 30), 255, 100,  0 );

}

void CScoreEntry::HandleEvents(SDL_Event& event)
{
	SDL_EnableUNICODE( SDL_ENABLE );

	// Get user input
	if(event.key.type == SDL_KEYDOWN)
	{
		if(userName.length() <= 3)
		{
			// if the key is a space
			if(event.key.keysym.unicode == (Uint16)' ')
			{
				// Append the character
				userName += (char)event.key.keysym.unicode;
			}
			// If the key is a number
			else if( ( event.key.keysym.unicode >= (Uint16)'0') && (event.key.keysym.unicode <= (Uint16)'9') )
			{
				// Append the character
				userName += (char)event.key.keysym.unicode;
			}
			else if( ( event.key.keysym.unicode >= (Uint16)'A') && (event.key.keysym.unicode <= (Uint16)'Z') )
			{
				// Append the character
				userName += (char)event.key.keysym.unicode;
			}
			else if( ( event.key.keysym.unicode >= (Uint16)'a') && (event.key.keysym.unicode <= (Uint16)'z') )
			{
				// Append the character
				userName += (char)event.key.keysym.unicode;
			}

		
			// If back space was pressed and the string isnt empty
			if( (event.key.keysym.sym == SDLK_BACKSPACE) && ( userName.length() != 0 ))
			{
				userName.erase( userName.length() -1);
			}

			if( (event.key.keysym.sym == SDLK_RETURN) && ( userName.length() != 0 ))
			{
				g_playername = userName;
				scrnManager->PopScreen();
			}

			event.key.type = (char)SDLK_UP;
		}

		// If window has been X'ed
		if( event.type == SDL_QUIT)
		{
			//run_app = false;
		}
	
		// If enter is pressed set done state to true

		
	}
}

void CScoreEntry::CleanUp( void )
{
	scrnEntityManager.RemoveEntity( pScoreEntryBorder );
	SDL_EnableUNICODE( SDL_ENABLE );
}

#include "../include/CGame.h"
#include "../include/CGlobalGameData.h"
#include <assert.h>

#define GRID_WIDTH 14
#define GRID_HEIGHT 14
#define LEVEL_SIZE_IN_TILES GRID_WIDTH * GRID_HEIGHT

#define BATT_START_POS_X 285
#define BATT_START_POS_Y 415
#define BATT_WIDTH 80
#define BATT_HEIGHT 20

#define BALL_START_POS_X BATT_START_POS_X + 30
#define BALL_START_POS_Y BATT_START_POS_Y - 20
#define BALL_WIDTH 20
#define BALL_HEIGHT 20

#define TILE_WIDTH 40
#define TILE_HEIGHT 20

// Global Object declarations

int g_topscore;

CGame::CGame( CSDLGraphics& graphics, CGlobalGameData& globalGameData )
	: IScreen( graphics, globalGameData ){

	this->graphics = &graphics;
}

bool CGame::init(){
	
	// Sprite used in the game screen
	ball = NULL;
	bat = NULL;
	arenaFrame = NULL;
	bkGround = NULL;

	bkGround = graphics->loadImageFromFile( "./images/BkGround00.png", 255, 0, 255 );
	arenaFrame = graphics->loadImageFromFile( "./images/Arena00.png", 255, 0, 255 );
	ball = graphics->loadImageFromFile( "./images/GameBall.png", 255, 0, 255 );
	bat = graphics->loadImageFromFile( "./images/Batt.png", 255, 0, 255 );
	yellowBlock = graphics->loadImageFromFile( "./images/BBlockYellow.png", 255, 0, 255 );
	blueBlock = graphics->loadImageFromFile( "./images/BBlockGreen.png", 255, 0, 255 );
	greenBlock = graphics->loadImageFromFile( "./images/BBlockBlue.png", 255, 0, 255 );

	ball_rect.x = BALL_START_POS_X;
	ball_rect.y = BALL_START_POS_Y;
	ball_rect.w = BALL_WIDTH;
	ball_rect.h = BALL_HEIGHT;
	
	bat_rect.x = BATT_START_POS_X;
	bat_rect.y = BATT_START_POS_Y;
	bat_rect.w = BATT_WIDTH;
	bat_rect.h = BATT_HEIGHT;

/*
	
	// Create moveable entities (bat and ball)
	
	// Create static entities (arena and grid for game blocks)
	
	//scrnEntityManager.AddEntity("PausedFrame.png", pPause, 0, 0);
	
	// Set conditons for pause box
	pPause->SetVisible( false );
	pPause->SetX( (SCREEN_WIDTH/2) - pPause->GetWidth() / 2); 
	pPause->SetY( (SCREEN_HEIGHT/2) - pPause->GetHeight() / 2 );
*/
	// Populate the screen with game blocks
	blocks = new CGrid(GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, TILE_HEIGHT, 40, 40 );

	// Collision detection object used to access collision detection functions
	collider = new CCollision();

	// Create timer to close beginning of level text
//	pText_timer = new CTimer();

	// Initialise score keeping
	m_score = 0;
//	UpdateScore( 0 );

	// Initialise lives counter
	m_lives = 3;
//	UpdateLives();

	// Set to first level
	levelNo = 0;

	// Set initial ball speed
	ball_speed = 8;

	// Set initial bat speed
	bat_speed = 9;

	// Set initial velocities for bat and ball
	ball_vel_x = -ball_speed;
	ball_vel_y = -ball_speed;

	bat_vel_x = bat_speed;
	
	// Get width and height of block for collisions detection
//	current_block.w = pArena_blocks->GetGridTileWidth();
//	current_block.h = pArena_blocks->GetGridTileHeight();

	// Is game over *should be IsAppRunning *
	m_QuitGame = false; 

	// Set the game to unpaused
	m_paused = false;

	// Set ball to initially not released
	m_ballReleased = true;

	// Set the level to inactive
	m_isLevelActive = false;
	
	// Track when level has begun, used for showing text
	m_isLevelStarted = false;

	// Flag for when to show text
	m_showIntroText = true;

	// Set up tracker for number of blocks that can be destoyed, used for tracking when the level is complete.
	m_totalNoBlocks= 0;

	// Load level data in to buffer
	if( LoadLevelFromFile( "leveldata.txt" ) != true){

		std::cout << "LoadLevelFromFile() failed to load data" << std::endl;
		return false;
	}


	// Load the level data from file
	setLevel( levelNo );	

	return true;
}

void CGame::render(){

	// Clear screen ready for the scene to be drawn over it
	graphics->clearScreen( 0, 0, 0);

	// Render screen entities
	graphics->draw( 0, 0, bkGround, SDL_GetVideoSurface(), NULL );
	graphics->draw( 0, 0, arenaFrame, SDL_GetVideoSurface(), NULL );

	graphics->draw( ball_rect.x, ball_rect.y, ball, SDL_GetVideoSurface(), NULL );
	graphics->draw( bat_rect.x, bat_rect.y, bat, SDL_GetVideoSurface(), NULL );

	// Render visible blocks
	
	// Iterate through the grid and draw the visible blocks
	coords *blockXY;

	for( int column = 0; column < GRID_HEIGHT; column++ ){
		for( int row = 0; row < GRID_WIDTH; row++ ){

			blockXY = blocks->getXY( row, column );

			if( blocks->getTileFlag( row, column ) != 0 ){
					
				// Fill out a gird of blocks with dimensions and the block image according to colour code
				switch( blocks->getTileFlag( row, column ) /*currentlevel[currentBlock]*/ )
				{
				case '1':
					graphics->draw( blockXY->x, blockXY->y, yellowBlock, SDL_GetVideoSurface(), NULL );
					break;
				case '2':
					graphics->draw( blockXY->x, blockXY->y, blueBlock, SDL_GetVideoSurface(), NULL );
					break;
				case '3':				
					graphics->draw( blockXY->x, blockXY->y, greenBlock, SDL_GetVideoSurface(), NULL );	
					break;
				default:
					break;
				}

				// Set solid block to active
				// pArena_blocks->SetGridStatus(j, i, 1);
				// Add it to the total number of block that can be destroyed
				m_totalNoBlocks++;
			}
		}
		
	}
		
	/*
	// Render score
	g_pRender->RenderText(score.str().c_str(), 7, SCREEN_HEIGHT - 35, 255, 0, 0 );
	g_pRender->RenderText(lives.str().c_str(), SCREEN_WIDTH - 60, SCREEN_HEIGHT - 35, 255, 0, 0 );
	g_pRender->RenderText("Score", 20, 425, 255, 0, 0);
	g_pRender->RenderText("Lives", 565, 425, 255, 0, 0);

	if( !m_isLevelActive )
	{
		// If not active show why
		if( m_lives <= 0 )
		{
			g_pRender->RenderText("Game Over", (SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 10, 255, 0, 0);
		}
	
		if( m_totalNoBlocks == 0 )
		{
			g_pRender->RenderText("Level Complete!", (SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 10, 255, 0, 0); // Needs timer aswell
			m_paused = false;
			m_isLevelActive = true;
			m_isLevelStarted = true;
			SDL_Delay( 8000 );
		}

	}

	if( m_showIntroText == true ) 
	{
		g_pRender->RenderText("Level 1, GO!", (SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 10, 255, 0, 0);
	}
*/
	graphics->update();
}

void CGame::update(){
/*
	if( m_paused )
	{
		return;
	}

	if( m_lives <= 0 )
	{
		m_isLevelActive = false;
		m_paused = true;
		g_topscore = m_score;
	//	scrnManager->ChangeScreen( 2 );
		return;
	}

	// If player out of lives or the number blocks have been eliminated then return
	if( m_totalNoBlocks <= 0)
	{
		m_isLevelActive = false;
		//m_paused = true;
		LoadLevel( ++m_levelNo );
		m_ballReleased = false;
		m_isLevelStarted = false;
		return;
	}

	if( m_isLevelStarted == false )
	{
	//	pText_timer->StartTimer();
		m_isLevelStarted = true;
	}

	if ( pText_timer->GetElapsedTime() > 2000 )
	{
		m_showIntroText = false;
	}
*/

	// Has ball been released? if not then use bats position
	if( !m_ballReleased )
	{
		ball_rect.x = bat_rect.x + ( bat_rect.w / 2 );
		ball_rect.y = bat_rect.y - ball_rect.h;
	}

	// Advance the ball using the current velocity THEN do collision detection to make post move modifications.
	ball_rect.x += ball_vel_x;
	ball_rect.y += ball_vel_y;


	// Has BAT collided with edge of arena
	if( bat_rect.x <= MIN_GAMEAREA_WIDTH ){

		bat_rect.x = MIN_GAMEAREA_WIDTH;
	}

	if( ( bat_rect.x + bat_rect.w ) >= MAX_GAMEAREA_WIDTH )
	{
		bat_rect.x = MAX_GAMEAREA_WIDTH - bat_rect.w;
	}

	// Has ball colided with bat, if so workout which direction it should bounce 
	if( collider->CheckCollide(ball_rect, bat_rect) == true )
	{	
		// Find the centres of the batt and ball
		int ballcentre = ball_rect.x + (ball_rect.w / 2);
		int batcentre = bat_rect.x + (bat_rect.w /2 );

		// If the ball hits the right edge of the bat bounce back in that direction
		if( ballcentre > (batcentre + 25) ){
			deflect( LEFT_EDGE, &ball_vel_x, &ball_vel_y);
			deflect( BOTTOM_EDGE, &ball_vel_x, &ball_vel_y );
		}
		// If the ball hits the left edge of the bat bounce back in that direction
		else if( ballcentre < (batcentre - 25) )
		{
			deflect( RIGHT_EDGE, &ball_vel_x, &ball_vel_y );
			deflect( BOTTOM_EDGE, &ball_vel_x, &ball_vel_y );
		}
		// If the ball hits the centre bounce as normal
		else{
			deflect( BOTTOM_EDGE, &ball_vel_x, &ball_vel_y );
		}
		
		return;
	}

	// Has ball collided with edge of arena, if so correct the position given the currently velocity and deflect the ball as necessary
	if( ball_rect.x + ball_vel_x <= MIN_GAMEAREA_WIDTH ){

		ball_rect.x = MIN_GAMEAREA_WIDTH;
		deflect( LEFT_EDGE, &ball_vel_x, &ball_vel_y );
		return;
	}

	if( ( ball_rect.x + ball_rect.w ) + ball_vel_x >= MAX_GAMEAREA_WIDTH ){

		ball_rect.x = ( MAX_GAMEAREA_WIDTH - ball_rect.w );
		deflect( RIGHT_EDGE, &ball_vel_x, &ball_vel_y );
		return;
	}
	
	if( ball_rect.y < MIN_GAMEAREA_HEIGHT ){

		ball_rect.y = MIN_GAMEAREA_HEIGHT;
		deflect(TOP_EDGE, &ball_vel_x, &ball_vel_y );
		return;
	}
	
	// Ball has hit the bottom edge of the screen
	if( ball_rect.y > MAX_GAMEAREA_HEIGHT){

		//UpdateLives();
		deflect( BOTTOM_EDGE, &ball_vel_x, &ball_vel_y );
		ball_rect.x = ( bat_rect.x + bat_rect.w / 2 );
		ball_rect.y = ( bat_rect.y - ball_rect.h );
		m_ballReleased = false;
		return;
		
	}

	// Iterate through the list of active blocks and check for collision
	bool Has_Collided = false;

	int collidedEdge = 0;

	for(int i = 0; i < GRID_WIDTH && Has_Collided != true; i++)
	{
		for(int j = 0; j < GRID_HEIGHT && Has_Collided != true; j++)
		{ 
			// ** consider putting some of the below in to functions to make it more readable **
			// If current block alive
			if( blocks->getTileFlag(i, j) > 0 )
			{
				coords *blockXY = blocks->getXY(i, j);
				SDL_Rect blockRect; 
				blockRect.x = blockXY->x;
				blockRect.y = blockXY->y;
				blockRect.w = TILE_WIDTH;
				blockRect.h = TILE_HEIGHT;
	
				// Find which edge ball collided with block and deflect accordingly
				if( collider->CheckCollide( ball_rect, blockRect )){
std::cout << "Collision" << std::endl;
					// Make the block in active so that it is no longer rendered
					blocks->setTileFlag(i, j, 0);
					// Increment score
					// UpdateScore( 10 );
					// Decremnt total number of blocks
					m_totalNoBlocks--;
					// Get what side of the current block the ball collided with and deflect accordingly
					switch( collider->CollisionEdge(ball_rect, blockRect) )
					{
						case BOTTOM_EDGE: // Ball collided with bottom edge of block 
							collidedEdge = TOP_EDGE;
							break;
						case TOP_EDGE:	  // Ball collided with top edge of block
							collidedEdge = BOTTOM_EDGE;
							break;
						case RIGHT_EDGE:  // Ball collided with right edge of block
							collidedEdge = LEFT_EDGE;
							break;
						case LEFT_EDGE:   // Ball collided with left edge of block
							collidedEdge = RIGHT_EDGE;
							break;
						case CORNER:      // Special case where ball hits the exact corner
							collidedEdge = CORNER;
							break;
						default:
							break;
					}
					deflect( collidedEdge, &ball_vel_x, &ball_vel_y );
					Has_Collided = true;		
				}
			}
		}
	}
	
}

void CGame::UpdateScore( unsigned int points)
{
	m_score += points;
//	score.str(" ");
//	score << m_score;
}

void CGame::UpdateLives()
{
	m_lives--;
//	lives.str("");
//	lives << m_lives;
}

// Deflect will reverse the direction of the ball given the side that is colliding
void CGame::deflect( unsigned int side, int* velX, int* velY)
{
	// Use the 'direction' variables to act as parameters to pass to the sprite setters
	// These are set to allow the ? : trick to work
	int directionX = *velX;
	int directionY = *velY;

	switch( side ){

	case TOP_EDGE:
		{
			if( ( *velX > 0 ) && ( *velY < 0) )
			{
				//Sprite must be moving right and up
				*velY = directionY < 0 ? -directionY : directionY;
			}

			if( ( *velX < 0 ) && ( *velY < 0 ) )
			{
				//Sprite must be moving left & up, so reveres this.
				*velY = directionY < 0 ? -directionY : directionY;
			}

			break;
		}
	case BOTTOM_EDGE:
		{
			if( ( *velX > 0 ) && ( *velY > 0) )
			{
				//Sprite must be moving right and down
				*velY = ( directionY > 0 ? -directionY : directionY );
			}
			
			if( ( *velX < 0 ) && ( *velY > 0 ) )
			{
				//Sprite must be moving left & down, so reveres this.
				*velY = ( directionY > 0 ? -directionY : directionY );
			}

			break;
		}
	case LEFT_EDGE:
		{
			if( ( *velX < 0 ) && ( *velY < 0 ) ){

				//Sprite must be moving up and left, so reveres this.
				*velX = ( directionX < 0 ) ? -directionX : directionX;
			}

			if( ( *velX < 0 ) && ( *velY > 0 ) ){

				//Sprite must be moving left & down, so reveres this.
				*velX = ( directionX < 0 ) ? -directionX : directionX;
			}
			
			break;
		}
	case RIGHT_EDGE:
		{
			if( ( *velX > 0 ) && ( *velY < 0) ){

				//Sprite must be moving right and up
				*velX = ( directionX > 0 ? -directionX : directionX );
			}

			if( ( *velX > 0 ) && ( *velY > 0) ){

				//Sprite must be moving right and down
				*velX = ( directionX > 0 ? -directionX : directionX );
			}
			break;
		}
	case CORNER:
		{
			*velX = directionX > 0 ? -directionX : directionX;
			*velY = directionY > 0 ? -directionY : directionY;
			break;
		}
	default:
		break;
	}
}


void CGame::processEvents( SDL_Event* event ){

	if(event->key.type == SDL_KEYDOWN)
	{
		switch( event->key.keysym.sym )
		{
			case SDLK_RIGHT:
			//	if(pBat->GetX() < (int)(MAX_GAMEAREA_WIDTH - pBat->GetWidth()) && !m_paused)
			//	{
			bat_rect.x += bat_vel_x;
			//	}
				break;
			case SDLK_LEFT:
			//	if(pBat->GetX() > MIN_GAMEAREA_WIDTH && !m_paused) 
			//	{
			bat_rect.x -= bat_vel_x;
			//	}
				break;
			break;
			case SDLK_SPACE:
				if ( !m_isLevelActive )
				{
					m_isLevelActive = true;
					break;
				}
				m_ballReleased = true;
			break;
			case SDLK_ESCAPE:
				m_QuitGame = true;
			break;
			case SDLK_F11:
				if(m_paused == true)
				{
					m_paused = false;
					//pPause->SetVisible( false );
				}
				else
				{
					m_paused = true;
					//pPause->SetVisible( true );
				}
			break;
			default:
				break;
		}
	}

	if( event->type == SDL_QUIT)
	{
		m_QuitGame = true;
	}
}

bool CGame::requestQuit(){

	if( m_QuitGame == true )
	{
		return true;
	}
	return false;
}

bool CGame::LoadLevelFromFile( std::string levelDataFile ){

	// Open file 
	std::ifstream level( levelDataFile.c_str(), std::ifstream::in);

	// Temporary storage for current line in data file
	std::string currentLine;

	// Level buffer
	std::string currentLevel;

	// Is file succesfully opened
	if( !level.good() )
	{
		std::cout << "Failed to open level data file" << std::endl;
		return false;
	}

	// Read in level data to buffer
	while( !level.eof() )
	{
		// Copy only the amount of line that fit in to each level
		for( int i = 0; i < GRID_HEIGHT; i++){
			std::getline(level, currentLine); // Read in one line
			currentLevel.append(currentLine); // Add it on to string to make one continous line
		}
		levels.push_back( currentLevel ); // Add this level to the levels vector
		std::getline(level, currentLine); // Read in blank line to get cursor down to the start of the next level
		currentLevel.clear(); // Clear buffer
	}

	// Close the file after reading in data
	level.close();

	// Data succesfully loaded
	std::cout << "Sucessfully opened level data file" << std::endl;
	
	return true;				
}

bool CGame::setLevel( unsigned int levelNo )
{

	std::string currentLevel = levels[ levelNo ];
	unsigned int currentTile = 0;
	for( int y = 0; y < GRID_HEIGHT; y++ ){
		for( int x = 0; x < GRID_WIDTH; x++ ){
				
			blocks->setTileFlag( x, y, currentLevel[currentTile] );		
			currentTile++;

		//	std::cout << "x = " << x << " y = " << y << " = " << currentLevel[currentTile] << std::endl;
		}
	}
	
	return true;
}

void CGame::cleanUp()
{

}

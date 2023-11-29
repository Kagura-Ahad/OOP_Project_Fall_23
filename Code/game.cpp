#include "game.hpp"
// #include "HUMania.hpp"
#include "drawing.hpp"

SDL_Renderer* Drawing::gRenderer = NULL;
SDL_Texture* Drawing::assets = NULL;

bool Game::init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Vampire Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			Drawing::gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( Drawing::gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( Drawing::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	// C:\Users\pc\Desktop\OOP Project\Graphics\background.png
	// Drawing::assets = loadTexture("assets.png");
    gTexture = loadTexture("C:/Users/pc/Desktop/OOP Project/Graphics/background.png");
    std::cout<<"Texture loaded successfully"<<std::endl;
	if(/*Drawing::assets==NULL ||*/ gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(Drawing::assets);
	Drawing::assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( Drawing::gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	Drawing::gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Drawing::gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

// Inside the Game class, add a variable to track the scrolling offset
int scrollingOffset = 0;

void Game::run()
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Update the scrolling offset to create the scrolling effect
        scrollingOffset -= 1; // Adjust the scrolling speed as needed

        // Render the background texture at the current scrolling offset
        SDL_Rect renderQuad = { scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderClear(Drawing::gRenderer);
        SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, &renderQuad);

        // Render a second copy of the background texture to create the continuous scrolling effect
        SDL_Rect renderQuad2 = { scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, &renderQuad2);

        // Check if the first copy of the texture has scrolled completely off-screen
        if (scrollingOffset <= -SCREEN_WIDTH)
        {
            scrollingOffset = 0;
        }

        SDL_RenderPresent(Drawing::gRenderer);
        SDL_Delay(10); // Adjust the delay to control the frame rate
    }
}
void Game::initVampire(SDL_Renderer* gRenderer)
{
	vampire.loadTexture(gRenderer, "C:/Users/AC/Desktop/OOP_Project_final/OOP_Project_Fall_23/Graphics/testgraphic.png");
}

void Game::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a: moveForward = true; break;
		case SDLK_d: moveBackward = true; break;
		case SDLK_w: jumping = true; break;
		default: break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a: moveForward = false; break;
		case SDLK_d: moveBackward = false; break;
		case SDLK_w: jumping = false; break;
		default: break;
		}
	}
}

void Game::update()
{
	const int playerSpeed = 5;
	const int playerJumpHeight = 10;
	if (moveForward)
	{
		vampire.move(playerSpeed, 0);
	}
	else if (moveBackward)
	{
		vampire.move(-playerSpeed, 0);
	}

	if (jumping)
	{
		if (moveForward)
		{
			vampire.move(playerSpeed, -playerJumpHeight);
		}
		else if (moveBackward)
		{
			vampire.move(-playerSpeed, -playerJumpHeight);
		}
		else
		{
			vampire.move(0, -playerJumpHeight);
		}
	}
}

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../common/debug.h"
#include "../common/carddatabase.h"
#include "../common/field.h"
#include "../common/texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* main_window;
SDL_Renderer* main_renderer;

bool init();
void quit();

int main(int argc, char* argv[])
{
	dbgInit("debug.txt");
	if(!init()) return 1;

	CardDatabase cdb;
	cdb.loadFile("test-db.txt");
	cdb.debug();

	TextureDatabase tdb;

	Field field;
	field.playCard(cdb, 0, false, true);
	field.playCard(cdb, 0, false, false);
	field.playCard(cdb, 0, false, false);

	//loop
	SDL_Event ev;
	bool running = true;
	while(running)
	{
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		
		//update game logic

		//clear
		SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
		SDL_RenderClear(main_renderer);
		SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);

		//draw
		field.draw(tdb, cdb, 20, 20, 0);

		//flip
		SDL_RenderPresent(main_renderer);
	}

	quit();
	dbgExit();
	return 0;
}

bool init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	main_window = SDL_CreateWindow(	"title", 
									SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH, SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN );

	if(!main_window)
	{
		printf("error creating window: %s\n", SDL_GetError());
		return false;
	}

	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if(!main_renderer)
	{
		printf("error creating renderer: %s\n", SDL_GetError());
		return false;
	}

	//Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

	return true;
}

void quit()
{
	IMG_Quit();

	if(main_renderer) SDL_DestroyRenderer(main_renderer);
	if(main_window) SDL_DestroyWindow(main_window);
	
	SDL_Quit();
}

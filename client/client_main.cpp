#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[])
{
	SDL_Window* main_window;
	SDL_Renderer* main_renderer;

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

		//flip
		SDL_RenderPresent(main_renderer);
	}

	IMG_Quit();

	if(main_renderer) SDL_DestroyRenderer(main_renderer);
	if(main_window) SDL_DestroyWindow(main_window);
	
	SDL_Quit();
}

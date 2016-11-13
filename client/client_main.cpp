#include <SDL.h>
#include <SDL_image.h>
#include <Leap.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../common/debug.h"
#include "../common/carddatabase.h"
#include "../common/field.h"
#include "../common/texture.h"
#include "../common/hand.h"
#include "../common/deck.h"
#include "../common/grave.h"
#include "SampleListener.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* main_window;
SDL_Renderer* main_renderer;

bool init();
void quit();


int main(int argc, char* argv[])
{
	int mouse_x = 0, mouse_y = 0;
	int mouse_start_x = 0, mouse_start_y = 0;

	srand(time(NULL));

	dbgInit("debug.txt");
	if(!init()) return 1;

	CardDatabase cdb;
	cdb.loadFile("test-db.txt");
	cdb.debug();

	TextureDatabase tdb;

	Field field;
	field.setPosition(20, 20);
	//field.playCard(cdb, 0, false, true);
	//field.playCard(cdb, 0, false, false);
	//field.playCard(cdb, 0, false, false);

	Hand hand;
	//hand.setPosition(320, 380);
	hand.setPosition(30, 380);

	Deck deck;
	deck.init(0, 7, 3);
	deck.setPosition(540, 120);

	for(int i = 0; i < 5; i++)
	{
		hand.addCard(deck.popCard());
	}

	Grave grave;
	grave.setPosition(540, 120 - CARD_HEIGHT);


	SampleListener listener;
	Leap::Controller controller;
	controller.addListener(listener);
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);

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

				case SDL_MOUSEBUTTONDOWN:
					if(ev.button.button == SDL_BUTTON_LEFT)
					{
						mouse_start_x = ev.button.x;
						mouse_start_y = ev.button.y;

						if(deck.isPointOnDeck(ev.button.x, ev.button.y))
							hand.addCard(deck.popCard());
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if(ev.button.button == SDL_BUTTON_LEFT)
					{
						mouse_x = ev.button.x;
						mouse_y = ev.button.y;
						int slot = field.pointToSlot(mouse_x, mouse_y);
						if(slot != -1)
						{
							//drag
							hand.playCardAt(cdb, mouse_start_x, mouse_start_y, false, field, slot);
						}

						slot = field.pointToSlot(mouse_start_x, mouse_start_y);
						if(grave.isPointOnGrave(mouse_x, mouse_y))
						{
							if(field.getSlotIndex(slot) != -1)
							{
								grave.setIndex(field.getSlotIndex(slot));
								field.setSlotIndex(slot, -1);
							}
						}
					}
			}
		}
		
		//update game logic
		SDL_GetMouseState(&mouse_x, &mouse_y);

		//clear
		SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
		SDL_RenderClear(main_renderer);
		SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);

		//draw
		field.draw(tdb, cdb, 0);
		hand.draw(tdb, cdb);
		grave.draw(tdb, cdb, 0);
		deck.draw(tdb, 0);

		//test
		//drawCard(tdb, cdb.getCardInfo(0), mouse_x, mouse_y, 0);

		//flip
		SDL_RenderPresent(main_renderer);

	}
	//remove the Leap Motion Listener
	controller.removeListener(listener);

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


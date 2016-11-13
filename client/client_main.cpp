#include <SDL.h>
#include <SDL_image.h>
#include <Leap.h>
#include <iostream>
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
#include "LeapListener.h"
#include "LeapMotion.h"

#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 720

SDL_Window* main_window;
SDL_Renderer* main_renderer;

bool init();
void quit();
bool getCoords(float *a, float *b, const Leap::Controller& controller, const LeapListener&
listener);

int main(int argc, char* argv[])
{
	int mouse_x, mouse_y;
    float leap_x, leap_y;
	int mouse_start_x = 0, mouse_start_y = 0;

	uint32_t last_gesture = 0xFFFF;
	uint32_t cur_gesture;

  	srand(time(NULL));

	dbgInit("debug.txt");
	if(!init()) return 1;

	CardDatabase cdb;
	cdb.loadFile("test-db.txt");
	cdb.debug();

	TextureDatabase tdb;

	Field field;
	field.setPosition(40, 40);
	//field.playCard(cdb, 0, false, true);
	//field.playCard(cdb, 0, false, false);
	//field.playCard(cdb, 0, false, false);

	Hand hand;
	//hand.setPosition(320, 380);
	hand.setPosition(30*2, SCREEN_HEIGHT - CARD_HEIGHT/2 - 40);

	Deck deck;
	deck.init(0, 7, 3);
	deck.setPosition(540*2 - 20, 120*2);

	for(int i = 0; i < 5; i++)
	{
		hand.addCard(deck.popCard());
	}

	Grave grave;
	grave.setPosition(540*2 - 20, 2*120 - CARD_HEIGHT);


	LeapListener listener;
	Leap::Controller controller;
	controller.addListener(listener);
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);
    if(!controller.isGestureEnabled(Leap::Gesture::TYPE_SWIPE)){
        controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
    }
    if(!controller.isGestureEnabled(Leap::Gesture::TYPE_KEY_TAP)){
       controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
       controller.config().setFloat ("Gesture.KeyTap.MinDownVelocity", 40.0f);
       controller.config().setFloat ("Gesture.KeyTap.HistorySeconds", .6f);
       controller.config().setFloat ("Gesture.KeyTap.MinDistance", 1.0f);
       controller.config().save();
    }
    if(!controller.isGestureEnabled(Leap::Gesture::TYPE_SCREEN_TAP)){
       controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP) ;
        controller.config().setFloat ("Gesture.ScreenTap.MinDownVelocity", 30.0);
        controller.config().setFloat("Gesture.ScreenTap.HistorySeconds", .5);
        controller.config().setFloat("Gesture.ScreenTap.MinDistance", 1.0);
        controller.config().save();
    }

    listener.onConnect(controller);

	int ticks, last_ticks = SDL_GetTicks();

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
						if(slot != -1 && grave.isPointOnGrave(mouse_x, mouse_y))
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

		ticks = SDL_GetTicks();
		
		bool is_hori = false;
		int type = 0;
		bool is_leap_valid = getCoords(&leap_x, &leap_y, controller, listener);
        int swipe_dir = LeapMotion::ProcessGestures(controller, &cur_gesture, &is_hori, &type);

		if(ticks - last_ticks > 1000)	//one gesture per sec
		{
			if(!is_hori)
			{
				if(swipe_dir == -1 ){
					//dbgPrint("-1 Yo");
					std::cout << "minus 1" << std::endl;
				}
				else if (swipe_dir == 1)
				{
					//dbgPrint("1 Yo");
					std::cout << "positive 1" << std::endl;
					
					if(cur_gesture != last_gesture)
					{
						hand.playCardAt(cdb, leap_x, 380*2, false, field, -1);
						last_gesture = cur_gesture;
						last_ticks = ticks;
					}

				} else {
				// dbgPrint("0 Yo");

				}
			}
			else
			{
				if(swipe_dir == 1 ){
					std::cout << "minus 1" << std::endl;

					if(cur_gesture != last_gesture)
					{
						//swipe left to draw cards
						//hand.addCard(deck.popCard());
						//last_gesture = cur_gesture;
						//last_ticks = ticks;
					}
				}
			}
			if(type == 1)
			{
				if(deck.isPointOnDeck(leap_x, leap_y))
				{
					hand.addCard(deck.popCard());
					last_gesture = cur_gesture;
					last_ticks = ticks;
				}
				else if(false)
				{

				}
				else
				{
					//tap to discard
					int slot = field.pointToSlot(leap_x, leap_y);
					if(slot != -1)
					{
						if(field.getSlotIndex(slot) != -1)
						{
							grave.setIndex(field.getSlotIndex(slot));
							field.setSlotIndex(slot, -1);
							last_gesture = cur_gesture;
							last_ticks = ticks;
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

		if(is_leap_valid)
		{
			drawCursor(tdb, leap_x, leap_y);
		}

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


//get the coordinates of where the hand in LeapMotoin is
bool getCoords(float *a, float *b, const Leap::Controller& controller, const LeapListener&
listener){

    Leap::Frame frame = controller.frame();
    Leap::Finger finger = frame.fingers().frontmost();
    Leap::Vector stabilizedPosition = finger.stabilizedTipPosition();
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector normalizedPosition = iBox.normalizePoint(stabilizedPosition);
    *a = normalizedPosition.x * SCREEN_WIDTH;
    *b = SCREEN_HEIGHT - normalizedPosition.y * SCREEN_HEIGHT;
	return finger.isValid();
}

void quit()
{
	IMG_Quit();

	if(main_renderer) SDL_DestroyRenderer(main_renderer);
	if(main_window) SDL_DestroyWindow(main_window);
	
	SDL_Quit();
}

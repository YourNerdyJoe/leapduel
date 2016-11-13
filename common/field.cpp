#include <SDL.h>
#include "field.h"
#include "texture.h"

void Field::playCard(int index, bool is_set, bool is_rot90)
{

}

#define SLOT_SIZE 100

void Field::draw(int x, int y, int angle)
{
	int i;
	for(i = 0; i < 10; i++)
	{
		SDL_Rect r = { x+(i%5)*SLOT_SIZE, y+(i>=5?SLOT_SIZE:0), SLOT_SIZE, SLOT_SIZE};
		SDL_RenderDrawRect(main_renderer, &r);
	}
}

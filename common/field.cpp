#include <SDL.h>
#include "field.h"
#include "texture.h"

void Field::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

bool Field::playCard(CardDatabase& cdb, int index, bool is_set, bool is_rot90)
{
	CardInfo& info = cdb.getCardInfo(index);
	if(info.type == CARD_MONSTER)
	{
		for(int i = 0; i < 5; i++)
		{
			if(card_slot[i].index == -1)
			{
				card_slot[i].index = index;
				card_slot[i].is_set = is_set;
				card_slot[i].is_rot90 = is_rot90;
				return true;
			}
		}
		return false;
	}
	else
	{
		for(int i = 5; i < 10; i++)
		{
			if(card_slot[i].index == -1)
			{
				card_slot[i].index = index;
				card_slot[i].is_set = is_set;
				card_slot[i].is_rot90 = false;
				return true;
			}
		}
		return false;
	}
}

#define SLOT_SIZE 100

void Field::draw(TextureDatabase& tdb, CardDatabase& cdb, int angle)
{
	int i;
	for(i = 0; i < 10; i++)
	{
		int card_x, card_y;
		SDL_Rect r;
		if(angle == 0)
		{
			r = { x+(i%5)*SLOT_SIZE, y+(i>=5?SLOT_SIZE:0), SLOT_SIZE, SLOT_SIZE };
			card_x = card_y = SLOT_SIZE/2;
		}
		else
		{
			r = { x+4*SLOT_SIZE-(i%5)*SLOT_SIZE, y+(i>=5?0:SLOT_SIZE), SLOT_SIZE, SLOT_SIZE };
			card_x = card_y = SLOT_SIZE/2;
		}
		
		SDL_RenderDrawRect(main_renderer, &r);
		
		int idx = card_slot[i].index;
		if(idx != -1)
		{
			int theta = angle + (card_slot[i].is_rot90?90:0);
			drawCard(tdb, cdb.getCardInfo(idx), r.x + card_x, r.y + card_y, theta);
		}
	}
}

int Field::pointToSlot(int xp, int yp)
{
	int left = xp - x;
	int top = xp - y;

	left /= SLOT_SIZE;
	top /= SLOT_SIZE;
	
}
#include "deck.h"

void Deck::init(int start, int end, int copies)
{
	for(int j = 0; j < copies; j++)
	{
		for(int i = start; i < end; i++)
		{
			int size = card_index.size();
			auto it = card_index.begin();
			if(size != 0)
			{
				int r = rand() % card_index.size();
				for(int k = 0; k < r; k++, it++);
			}
			
			card_index.insert(it, i);
		}
	}
}

void Deck::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

void Deck::draw(TextureDatabase& tdb, int angle)
{
	if(card_index.empty()) return;

	SDL_Rect src = { 0, 0, 297, 432 };
	SDL_Rect dst = { x, y, CARD_WIDTH, CARD_HEIGHT };

	SDL_Point center = { CARD_WIDTH/2, CARD_HEIGHT/2 };

	SDL_RenderCopyEx(main_renderer,
		tdb.getLoadTexture("cardback.jpg"),
		&src,
		&dst,
		(double)angle,
		&center,
		SDL_FLIP_NONE);
}

bool Deck::isPointOnDeck(int xp, int yp)
{
	int left = x;
	int top = y;

	if(card_index.empty()) return false;

	if(xp >= left && xp < left + CARD_WIDTH && 
		yp >= top && yp < top + CARD_HEIGHT)
	{
		return true;
	}
	return false;
}

int Deck::popCard()
{
	int ret = card_index.back();
	card_index.pop_back();
	return ret;
}

#include "deck.h"

void Deck::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

void Deck::draw(TextureDatabase& tdb, int angle)
{
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

	if(xp >= left && xp < left + CARD_WIDTH && 
		yp >= top && yp < top + CARD_HEIGHT)
	{
		return true;
	}
	return false;
}

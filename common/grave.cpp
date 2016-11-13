#include "grave.h"

void Grave::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

void Grave::setIndex(int idx)
{
	index = idx;
}

void Grave::draw(TextureDatabase& tdb, CardDatabase& cdb, int angle)
{
	if(index == -1) drawCardBlank(x, y);
	else drawCard(tdb, cdb.getCardInfo(index), x + CARD_WIDTH/2, y + CARD_HEIGHT/2, angle);
}

bool Grave::isPointOnGrave(int xp, int yp)
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

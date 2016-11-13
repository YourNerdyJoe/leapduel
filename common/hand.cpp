#include "hand.h"

void Hand::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

void Hand::draw(TextureDatabase& tdb, CardDatabase& cdb)
{
	int i = 0;
	int size = card_index.size();
	int offset = (size-1)*50;
	for(auto it = card_index.begin(); it != card_index.end(); it++, i++)
	{
		drawCard(tdb, cdb.getCardInfo(*it), x+100*i-offset, y, 0);
	}
}

void Hand::addCard(int index)
{
	card_index.push_back(index);
}

int Hand::getCardAt(int x, int y)
{
	return -1;
}

int Hand::playCardAt(int x, int y, Field& field)
{
	return -1;
}

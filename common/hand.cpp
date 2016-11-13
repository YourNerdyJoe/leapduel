#include "hand.h"

void Hand::setPosition(int xp, int yp)
{
	x = xp;
	y = yp;
}

void Hand::draw(TextureDatabase& tdb, CardDatabase& cdb)
{
	/*int i = 0;
	int size = card_index.size();
	int offset = (size-1)*50;
	for(auto it = card_index.begin(); it != card_index.end(); it++, i++)
	{
		drawCard(tdb, cdb.getCardInfo(*it), x+100*i-offset, y, 0);
	}*/
	int i = 0;
	//int size = card_index.size();
	//int offset = 20;;
	for(auto it = card_index.begin(); it != card_index.end(); it++, i++)
	{
		drawCard(tdb, cdb.getCardInfo(*it), x+200*i+CARD_WIDTH/2, y, 0);
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

bool Hand::playCardAt(CardDatabase& cdb, int xp, int yp, bool is_set, Field& field, int slot)
{
	if(yp >= y - CARD_HEIGHT/2)
	{
		xp -= x;
		int card_x = xp / 200;
		int size = card_index.size();
		if(card_x < size)
		{
			auto it = card_index.begin();
			std::advance(it, card_x);
			int index = *it;
			if(field.playCard(cdb, index, is_set, false, slot))
			{
				card_index.erase(it);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

#ifndef _HAND_H_
#define _HAND_H_
#include <list>
#include "field.h"

class Hand
{
	int x, y;
	std::list<int> card_index;

public:
	void setPosition(int x, int y);
	void draw(TextureDatabase& tdb, CardDatabase& cdb);
	void addCard(int index);

	int getCardAt(int x, int y);
	int playCardAt(int x, int y, Field& field, int slot);
};

#endif

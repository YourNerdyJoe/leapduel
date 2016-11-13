#ifndef _DECK_H_
#define _DECK_H_
#include <list>
#include "texture.h"

class Deck
{
	int x, y;
	std::list<int> card_index;

public:
	void init(int start, int end, int copies);

	void setPosition(int x, int y);
	void draw(TextureDatabase& tdb, int angle);

	bool isPointOnDeck(int x, int y);

	int popCard();
};

#endif

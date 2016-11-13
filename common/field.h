#ifndef _FIELD_H_
#define _FIELD_H_
#include "texture.h"
#include "carddatabase.h"

class Field
{
	struct CardSlot
	{
		int index;
		bool is_set;
		bool is_rot90;

		inline CardSlot(): index(-1), is_set(false), is_rot90(false) {}
		inline CardSlot(int index, bool is_set, bool is_rot90): index(index), is_set(is_set), is_rot90(is_rot90) {}
	};

	CardSlot card_slot[10];

public:
	bool playCard(CardDatabase& cdb, int index, bool is_set, bool is_rot90);
	void draw(TextureDatabase& tdb, CardDatabase& cdb, int x, int y, int angle);
};

#endif

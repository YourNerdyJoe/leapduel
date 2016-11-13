#ifndef _FIELD_H_
#define _FIELD_H_

class Field
{
	struct CardSlot
	{
		int index;
		bool is_set;
		bool is_rot90;

		inline CardSlot() {}
		inline CardSlot(int index, bool is_set, bool is_rot90): index(index), is_set(is_set), is_rot90(is_rot90) {}
	};

	CardSlot card_slot[10];

public:
	void playCard(int index, bool is_set, bool is_rot90);
	void draw(int x, int y, int angle);
};

#endif

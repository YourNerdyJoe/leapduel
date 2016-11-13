#ifndef _CARD_DATABASE_H_
#define _CARD_DATABASE_H_
#include <vector>
#include "cardinfo.h"

class CardDatabase
{
	std::vector<CardInfo> card_info;

public:
	bool loadFile(const char* filename);
	void debug();

	inline CardInfo& getCardInfo(int index) { return card_info[index]; }
};

#endif

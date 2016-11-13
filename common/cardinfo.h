#ifndef _CARDINFO_H_
#define _CARDINFO_H_
#include <string>

enum CardType
{
	CARD_UNKNOWN = 0,
	CARD_MONSTER,
	CARD_SPELL,
	CARD_TRAP,
};

struct CardInfo
{
	std::string name;
	std::string texture;
	CardType type;
	int atk, def;
	std::string description;
};

#endif

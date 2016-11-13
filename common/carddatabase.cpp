#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carddatabase.h"
#include "debug.h"

char buf [256];
const char* getString(FILE* f)
{
	buf[0] = 0;
	fgets(buf, 256, f);
	int end = strlen(buf);
	if(end > 0 && buf[end-1] == '\n') buf[end-1] = 0;
	return buf;
}

int getInt(FILE* f)
{
	int ret;
	ret = atoi(getString(f));
	return ret;
}

bool CardDatabase::loadFile(const char* filename)
{
	FILE* f = fopen(filename, "r");
	if(!f)
	{
		dbgPrint(DBG_ERROR "Unable to open file '%s'\n", filename);
		return false;
	}

	//int count = getInt(f);
	//for(int i = 0; i < count; i++)
	while(!feof(f))
	{
		CardInfo info;
		info.name = getString(f);
		info.texture = getString(f);
		info.type = (CardType)getInt(f);
		info.atk = getInt(f);
		info.def = getInt(f);
		info.description = getString(f);

		card_info.push_back(info);
	}

	return true;
}

void CardDatabase::debug()
{
	size_t i, len = card_info.size();
	dbgPrint("cards: %u\n", len);
	for(i = 0; i < len; i++)
	{
		CardInfo& info = card_info[i];

		dbgPrint("%s\n%s\n%d\n%d\n%d\n%s\n",
			info.name.c_str(),
			info.texture.c_str(),
			info.type,
			info.atk,
			info.def,
			info.description.c_str());
	}
}

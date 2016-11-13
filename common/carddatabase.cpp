#include <fstream>
#include "carddatabase.h"
#include "debug.h"

char buf [256];
const char* getString(FILE* f)
{
	fscanf(f, "%s", buf);
	return buf;
}

int getInt(FILE* f)
{
	int ret;
	fscanf(f, "%d", &ret);
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

	while(!feof(f))
	{
		try
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
		catch(std::exception e)
		{
			dbgPrint(DBG_ERROR "error while reading file '%s'", filename);
			return false;
		}
	}

	return true;
}

void CardDatabase::debug()
{
	size_t i, len = card_info.size();
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
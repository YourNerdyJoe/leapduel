#ifndef _GRAVE_H_
#define _GRAVE_H_
#include "texture.h"
#include "carddatabase.h"

class Grave
{
	int x, y;
	int index;

public:
	inline Grave(): index(-1) {}

	void setPosition(int x, int y);
	void setIndex(int idx);

	void draw(TextureDatabase& tdb, CardDatabase& cdb, int angle);
	bool isPointOnGrave(int x, int y);
};

#endif

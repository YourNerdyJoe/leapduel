#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <map>
#include <SDL.h>
#include <string>
#include "cardinfo.h"

#define CARD_WIDTH 80
#define CARD_HEIGHT 100

struct Texture
{
	std::string name;
	SDL_Texture* texture;

	bool load(const char* filename);
	void destroy();
};

class TextureDatabase
{
	std::map<const std::string, Texture> texture_list;

public:
	SDL_Texture* getTexture(const char* name);
	SDL_Texture* getLoadTexture(const char* name);

	~TextureDatabase();
};


void drawCard(TextureDatabase& tdb, CardInfo& info, int x, int y, int angle);
void drawCardBlank(int x, int y);
void drawCursor(TextureDatabase& tdb, int x, int y);

extern SDL_Renderer* main_renderer;

#endif

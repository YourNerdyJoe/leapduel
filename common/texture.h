#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <map>
#include <SDL.h>
#include <string>
#include "cardinfo.h"

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

extern SDL_Renderer* main_renderer;

#endif
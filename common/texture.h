#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <map>
#include <SDL.h>
#include <string>

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
	Texture* getTexture(const char* name);
	Texture* getLoadTexture(const char* name);

	~TextureDatabase();
};

extern SDL_Renderer* main_renderer;

#endif

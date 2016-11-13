#include "texture.h"
#include <SDL_image.h>
#include "debug.h"
#include "carddatabase.h"

extern SDL_Renderer* main_renderer;
const std::string texture_dir = "textures/";

bool Texture::load(const char* filename)
{
	name = filename;

	std::string path = texture_dir;
	path += name;
	
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(!surface)
	{
		dbgPrint(DBG_ERROR "Unable to load Texture '%s'\n\t%s\n", filename, SDL_GetError());
		return false;
	}
	
	texture = SDL_CreateTextureFromSurface(main_renderer, surface);
	if(!texture)
	{
		dbgPrint(DBG_ERROR "Unable to create Texture '%s' from SDL_Surface\n\t%s\n", filename, SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surface);

	dbgPrint("Loaded Texture '%s'\n", filename);

	return true;
}

void Texture::destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

SDL_Texture* TextureDatabase::getTexture(const char* name)
{
	auto it = texture_list.find(name);
	if(it != texture_list.end())
	{
		return it->second.texture;
	}
	else
	{
		return nullptr;
	}
}

SDL_Texture* TextureDatabase::getLoadTexture(const char* name)
{
	SDL_Texture* ret = getTexture(name);
	if(!ret)
	{
		Texture tex;
		tex.load(name);
		texture_list[name] = tex;
		ret = getTexture(name);	//why not
	}
	return ret;
}

TextureDatabase::~TextureDatabase()
{
	for(auto it = texture_list.begin(); it != texture_list.end(); it++)
	{
		it->second.destroy();
	}
}


void drawCard(TextureDatabase& tdb, CardInfo& info, int x, int y, int angle)
{
	SDL_Rect dst = { x - CARD_WIDTH/2, y - CARD_HEIGHT/2, CARD_WIDTH, CARD_HEIGHT };
	SDL_Rect src = { 0, 0, 167, 245 };

	SDL_Point center = { CARD_WIDTH/2, CARD_HEIGHT/2 };

	SDL_RenderCopyEx(main_renderer, 
		tdb.getLoadTexture(info.texture.c_str()),
		&src,
		&dst,
		(double)angle,
		&center,
		SDL_FLIP_NONE);
}

void drawCardBlank(int x, int y)
{
	SDL_Rect dst = { x - CARD_WIDTH/2, y - CARD_HEIGHT/2, CARD_WIDTH, CARD_HEIGHT };
	SDL_Rect src = { 0, 0, 167, 245 };

	SDL_Point center = { CARD_WIDTH/2, CARD_HEIGHT/2 };

	SDL_RenderCopyEx(main_renderer, 
		nullptr,
		&src,
		&dst,
		0.0,
		&center,
		SDL_FLIP_NONE);
}

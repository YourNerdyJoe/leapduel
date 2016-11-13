#include "texture.h"
#include <SDL_image.h>
#include "debug.h"

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

Texture* TextureDatabase::getTexture(const char* name)
{
	auto it = texture_list.begin();
	if(it != texture_list.end())
	{
		return &it->second;
	}
	else
	{
		return nullptr;
	}
}

Texture* TextureDatabase::getLoadTexture(const char* name)
{
	Texture* ret = getTexture(name);
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

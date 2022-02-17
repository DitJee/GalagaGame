#pragma once
#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>

// *******************************************
// ******* serve as a cache for assets *******
// *******************************************

class AssetManager 
{
private:
	static AssetManager* sInstance;

	std::map<std::string, SDL_Texture*> mTextures;
	std::map<std::string, SDL_Texture*> mTexts;
	std::map<std::string, TTF_Font*>    mFonts;
	std::map<std::string, Mix_Music*> mMusics;
	std::map<std::string, Mix_Chunk*> mSFXs;

public:

	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(const std::string& filename);
	SDL_Texture* GetText(const std::string& text, const std::string& filename, int size, SDL_Color color);

	Mix_Music* GetMusic(const std::string& filename);
	Mix_Chunk* GetSFX(const std::string& filename);
private:
	AssetManager();
	~AssetManager();

	TTF_Font* GetFont(const std::string& filename, int size);
};
#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL;

AssetManager* AssetManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AssetManager();

		return sInstance;
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	// iterate through map of textures and destroy it
	for (auto texture: mTextures)
	{
		if (texture.second != NULL)
		{
			SDL_DestroyTexture(texture.second);
		}
	}

	mTextures.clear();

	// clear texts
	for (auto text : mTexts)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	mTexts.clear();

	// clear Fonts
	for (auto font : mFonts)
	{
		if (font.second != NULL)
		{
			TTF_CloseFont(font.second);
		}
	}

	mFonts.clear();

	// clear music
	for (auto music : mMusics)
	{
		if (music.second != NULL)
		{
			Mix_FreeMusic(music.second);
		}
	}

	mMusics.clear();

	// clear SFX
	for (auto SFX : mSFXs)
	{
		if (SFX.second != NULL)
		{
			Mix_FreeChunk(SFX.second);
		}
	}

	mSFXs.clear();
}

SDL_Texture* AssetManager::GetTexture(const std::string& filename)
{
	std::string FullPath = SDL_GetBasePath();
	FullPath.append("Assets/" + filename);

	if (mTextures[FullPath] == nullptr)
	{
		mTextures[FullPath] = Graphics::Instance()->LoadTexture(FullPath);
	}
	
	return mTextures[FullPath];
}

TTF_Font* AssetManager::GetFont(const std::string& filename, int size)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets\\" + filename);

	std::string key = fullPath + (char)size;

	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size); 

		if (mFonts[key] == nullptr)
		{
			printf("font loading error: %s from font: %s\n", TTF_GetError(), filename.c_str());
		}
	}

	return mFonts[key];
}

SDL_Texture* AssetManager::GetText(const std::string& text, const std::string& filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);

	std::string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (mTexts[key] == nullptr)
	{
		mTexts[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	}
	return mTexts[key];
}

Mix_Music* AssetManager::GetMusic(const std::string& filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets\\" + filename);

	if (mMusics[fullPath] == nullptr)
	{
		mMusics[fullPath] = Mix_LoadMUS(fullPath.c_str());

		if (mMusics[fullPath] == nullptr)
		{
			printf("Music loading error: %s from file: %s\n", Mix_GetError(), filename.c_str());
		}
	}

	return mMusics[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(const std::string& filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets\\" + filename);

	if (mSFXs[fullPath] == nullptr)
	{
		mSFXs[fullPath] = Mix_LoadWAV(fullPath.c_str());

		if (mSFXs[fullPath] == nullptr)
		{
			printf("SFX loading error: %s from file: %s\n", Mix_GetError(), filename.c_str());
		}
	}

	return mSFXs[fullPath];
}

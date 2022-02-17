#pragma once
#include "GameEntity.h"
#include "AssetManager.h"
class Texture : public GameEntity
{
protected:

	SDL_Texture* mTexture;
	Graphics* mGraphics;

	int mHeight;
	int mWidth;

	SDL_Rect mRenderRect;

	bool mClipped;
	SDL_Rect mClippedRect;

public:

	Texture(const std::string& filename);
	Texture(const std::string& filename, int x, int y, int w, int h);

	// override for text
	Texture(const std::string& text, const std::string& fontPath, int size, SDL_Color color);
	~Texture();

	virtual void Render();
};
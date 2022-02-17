#include "Texture.h"

Texture::Texture(const std::string& filename)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth , &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(const std::string& filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClippedRect.x = x;
	mClippedRect.y = y;
	mClippedRect.w = mWidth;
	mClippedRect.h = mHeight;

}

Texture::Texture(const std::string& text, const std::string& fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();

	mTexture = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	mTexture = NULL;
	mGraphics = NULL;
}

void Texture::Render()
{
	// get world position
	Vector2 pos = Pos(SPACE::world);

	// get scale
	Vector2 scale = Scale(SPACE::world);

	// render the texture at the center of position
	mRenderRect.x = (int)(pos.x - mWidth  * scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
	mRenderRect.w = (int)(mWidth  * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTexture, (mClipped) ? &mClippedRect : NULL, &mRenderRect, Rotation(SPACE::world));
}

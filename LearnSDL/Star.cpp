#include "Star.h"

bool Star::sScroll = false;

void Star::Scroll(bool b)
{
	sScroll = b;
}

Star::Star(int layer)
	: Texture("Stars.png", 0, 0, 3	, 3)
{
	mTimer = QuickSDL::Timer::Instance();

	int starColor = rand() % 4;

	mClippedRect.x = starColor * 3;

	Pos(QuickSDL::Vector2(rand() % QuickSDL::Graphics::SCREEN_WIDTH, rand() % QuickSDL::Graphics::SCREEN_HEIGHT));

	mFlickerTimer = 0.0f;
	mFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f;

	// star size
	float inverseLayer = 1.0f / layer;
	Scale(QuickSDL::VEC2_ONE * inverseLayer);

	// speed
	mScrollSpeed = 5.0f / layer;
}

Star::~Star()
{
	mTimer = NULL;
}

void Star::ScrollStar()
{
	Translate(QuickSDL::VEC2_UP * mScrollSpeed);

	QuickSDL::Vector2 pos = Pos(QuickSDL::GameEntity::SPACE::local);

	if (pos.y > QuickSDL::Graphics::SCREEN_HEIGHT)
	{
		pos.y = 0.0f;
		pos.x = rand() % QuickSDL::Graphics::SCREEN_WIDTH;
		Pos(pos);
	}
}

void Star::Update()
{
	mFlickerTimer += mTimer->DeltaTime();

	if (mFlickerTimer >= mFlickerSpeed)
	{
		mIsVisble = !mIsVisble;
		mFlickerTimer = 0.0f;
	}

	if (sScroll)
	{
		ScrollStar();
	}
}

void Star::Render()
{
	if (mIsVisble)
	{
		QuickSDL::Texture::Render();
	}
}
#include "BackgroundStar.h"

BackgroundStar* BackgroundStar::sInstance = NULL;

BackgroundStar* BackgroundStar::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new BackgroundStar();
	}
	return sInstance;
}

void BackgroundStar::Release()
{
	delete sInstance;
	sInstance = NULL;
}

BackgroundStar::BackgroundStar()
{
	for (size_t i = 0; i < LAYER_COUNT; i++)
	{
		mLayers[i] = new StarLayer(i);
	}
}

BackgroundStar::~BackgroundStar()
{
	for (size_t i = 0; i < LAYER_COUNT; i++)
	{
		delete mLayers[i];
		mLayers[i] = NULL;
	}
}

void BackgroundStar::Scroll(bool b)
{
	Star::Scroll(b);
}

void BackgroundStar::Update()
{
	for (size_t i = 0; i < LAYER_COUNT; i++)
	{
		mLayers[i]->Update();
	}
}

void BackgroundStar::Render()
{
	for (size_t i = 0; i < LAYER_COUNT; i++)
	{
		mLayers[i]->Render();
	}
}
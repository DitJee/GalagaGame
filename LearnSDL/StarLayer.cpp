#include "StarLayer.h"

StarLayer::StarLayer(int layer)
{
	for (size_t i = 0; i < STAR_COUNT; i++)
	{
		mStars[i] = new Star(layer);
	}
}

StarLayer::~StarLayer()
{
	for (size_t i = 0; i < STAR_COUNT; i++)
	{
		delete mStars[i];
		mStars[i] = NULL;
	}
}

void StarLayer::Update()
{
	for (size_t i = 0; i < STAR_COUNT; i++)
	{
		mStars[i]->Update();
	}
}

void StarLayer::Render()
{
	for (size_t i = 0; i < STAR_COUNT; i++)
	{
		mStars[i]->Render();
	}
}

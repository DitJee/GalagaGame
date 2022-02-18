#pragma once
#include "StarLayer.h"
class BackgroundStar
{
private:
	static BackgroundStar* sInstance;

	static const int LAYER_COUNT = 3;
	StarLayer* mLayers[LAYER_COUNT];

public:
	static BackgroundStar* Instance();
	static void Release();

	void Scroll(bool b);

	void Update();
	void Render();

private:
	BackgroundStar();
	~BackgroundStar();
};
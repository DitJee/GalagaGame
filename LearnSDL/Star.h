#pragma once

#include "Texture.h"
#include "Timer.h"

class Star : public QuickSDL::Texture
{
private:

	static bool sScroll;

	QuickSDL::Timer* mTimer;

	bool mIsVisble;
	float mFlickerTimer;
	float mFlickerSpeed;

	float mScrollSpeed;

public:

	static void Scroll(bool b);

	Star(int layer);
	~Star();

	void Update();
	void Render();

private:

	void ScrollStar();
};
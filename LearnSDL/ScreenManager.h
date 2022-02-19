#pragma once
#include "StartScreen.h"
#include "BackgroundStar.h"
#include "PlayScreen.h"

class ScreenManager
{
private:

	enum class SCREENS : Uint8
	{
		start,
		play
	};

	static ScreenManager* sInstance;

	QuickSDL::InputManager* mInputManager;

	BackgroundStar* mBackgroundStar;
	StartScreen* mStartScreen;

	SCREENS mCurrentScreen;

	PlayScreen* mPlayScreen;

public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
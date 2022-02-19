#pragma once
#include "InputManager.h"
#include "BackgroundStar.h"
#include "PlayScreenSideBar.h"

class PlayScreen : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::InputManager* mInputManager;

	BackgroundStar* mBackgroundStar;

	PlayScreenSideBar* mSideBar;

public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();
};
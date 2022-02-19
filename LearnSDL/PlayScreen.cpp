#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = QuickSDL::Timer::Instance();
	mInputManager = QuickSDL::InputManager::Instance();

	mBackgroundStar = BackgroundStar::Instance();

	mSideBar = new PlayScreenSideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH *0.85f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.05f));

	mSideBar->SetHighScore(10000);

	mSideBar->SetShips(70);
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInputManager = NULL;
	mBackgroundStar = NULL;

	delete mSideBar;
	mSideBar = NULL;
}

void PlayScreen::Update()
{
	mSideBar->Update();
}

void PlayScreen::Render()
{
	mSideBar->Render();
}


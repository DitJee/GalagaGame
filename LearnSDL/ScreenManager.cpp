#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

void ScreenManager::Update()
{
	mBackgroundStar->Update();

	switch (mCurrentScreen)
	{
	case ScreenManager::SCREENS::start:
		mStartScreen->Update();

		// change to play by pressing `enter`
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = SCREENS::play;
			mStartScreen->ResetAnimation();
		}

		break;
	case ScreenManager::SCREENS::play:

		// change to start menu by pressing `esc`
		if (mInputManager->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = SCREENS::start;
			//mStartScreen->ResetAnimation();
		}

		break;
	default:
		break;
	}
}

void ScreenManager::Render()
{
	mBackgroundStar->Render();

	switch (mCurrentScreen)
	{
	case ScreenManager::SCREENS::start:
		mStartScreen->Render();

		break;
	case ScreenManager::SCREENS::play:
		break;
	default:
		break;
	}
}

ScreenManager::ScreenManager()
{
	mInputManager = QuickSDL::InputManager::Instance();

	mBackgroundStar = BackgroundStar::Instance();
	mStartScreen = new StartScreen;

	mCurrentScreen = SCREENS::start;
}

ScreenManager::~ScreenManager()
{
	mInputManager = NULL; // got released in GameManager

	mBackgroundStar->Release();

	delete mStartScreen;
	mStartScreen = NULL;
}

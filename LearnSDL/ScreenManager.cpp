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
			mPlayScreen->StartNewGame();
		}

		break;
	case ScreenManager::SCREENS::play:

		mPlayScreen->Update();
		
		if (mPlayScreen->GameOver())
		{
			mCurrentScreen = SCREENS::start;
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
		mPlayScreen->Render();
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
	mPlayScreen = new PlayScreen();

	mCurrentScreen = SCREENS::start;
}

ScreenManager::~ScreenManager()
{
	mInputManager = NULL; // got released in GameManager

	mBackgroundStar->Release();

	delete mStartScreen;
	delete mPlayScreen;

	mStartScreen = NULL;
	mPlayScreen = NULL;
}

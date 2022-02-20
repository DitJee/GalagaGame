#include "PlayScreen.h"


PlayScreen::PlayScreen()
{
	mTimer = QuickSDL::Timer::Instance();
	mInputManager = QuickSDL::InputManager::Instance();
	mAudioManager = QuickSDL::AudioManager::Instance();

	mBackgroundStar = BackgroundStar::Instance();

	mSideBar = new PlayScreenSideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH *0.85f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.05f));

	mStartLabel = new QuickSDL::Texture("START", "myFont.ttf", 32, {150,0,0});
	mStartLabel->Parent(this);
	mStartLabel->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.4f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.5f));

	mLevelStartDelay = 1.f;
	mLevelStarted = false;

	mLevel = NULL;
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInputManager = NULL;
	mBackgroundStar = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.f;
	mLevelStarted = true;
	
	delete mLevel;

	mLevel = new Level(mCurrentStage, mSideBar);
}


void PlayScreen::StartNewGame()
{
	mBackgroundStar->Scroll(false);
	mSideBar->SetHighScore(10000);
	mSideBar->SetShips(2);

	mGameStarted = false; // dont start immediately
	mAudioManager->PlayMusic("StartSound.wav", 0); // play once
	mCurrentStage = 10;
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		// level start logic
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();

			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}
	}
	else
	{
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}

	if (mGameStarted && mLevelStarted)
	{
		mSideBar->Update();
		mLevel->Update();
	}

}

void PlayScreen::Render()
{
	mSideBar->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
		
	}

	if (mGameStarted && mLevelStarted)
	{
		mLevel->Render();
	}
}


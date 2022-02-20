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

	mPlayer = NULL;
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

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.f;
	mLevelStarted = true;
	
	delete mLevel;

	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);
}


void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.4f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.85f));
	mPlayer->Active(false);

	mBackgroundStar->Scroll(false);

	mSideBar->SetHighScore(10000);
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false; // dont start immediately

	mLevelStarted = false;
	mLevelStartTimer = 0.0f;

	mAudioManager->PlayMusic("StartSound.wav", 0); // play once
	mCurrentStage = 0;
}

bool PlayScreen::GameOver()
{
	if (!mLevelStarted)
	{
		return false;
	}

	return (mLevel->State() == Level::LEVEL_STATES::gameover);
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

	if (mGameStarted)
	{
		if (mCurrentStage > 0)
		{
			mSideBar->Update();
		}

		if (mLevelStarted)
		{
			mLevel->Update();

			if (mLevel->State() == Level::LEVEL_STATES::finished)
			{
				mLevelStarted = false;
			}
		}

		mPlayer->Update();
		
	}

}

void PlayScreen::Render()
{
	mSideBar->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
		
	}

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Render();

		}

		mPlayer->Render();
	}
}


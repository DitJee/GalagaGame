#include "Level.h"


Level::Level(int stage, PlayScreenSideBar* sideBar, Player* player)
{
	mTimer = QuickSDL::Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(stage);
	mBackgroundStar = BackgroundStar::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new QuickSDL::Texture("STAGE", "myFont.ttf", 32, { 75,75,200 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.35f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.5f));

	mStageNumber = new ScoreBoard({ 75,75,200 });
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.5f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.5f));

	mStageLabelOnScreen = 0.f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new QuickSDL::Texture("READY", "myFont.ttf", 32, { 150,0,0});
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.4f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 1.5f;

	mPlayer = player;

	mPlayerHit = false;
	mPlayerRespawnDelay = 3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new QuickSDL::Texture("GAMEOVER", "myFont.ttf", 32, { 150,0,0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.4f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay =4.0f;
	mGameOverTimer = 0.0f;
	mGameOverOnScreen = 1.0f;

	mCurrentState = LEVEL_STATES::running;
}

Level::~Level()
{
	mTimer = NULL;
	mSideBar = NULL;
	mBackgroundStar = NULL;

	delete mStageLabel;
	mStageLabel = NULL;

	delete mStageNumber;
	mStageNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;
}


void Level::StartStage()
{
	mStageStarted = true;
}

void Level::HandleStartLabels()
{
	mLabelTimer += mTimer->DeltaTime();

	if (mLabelTimer >= mStageLabelOffScreen)
	{
		mBackgroundStar->Scroll(true);

		if (mStage > 1)
		{
			StartStage();
		}
		else
		{
			if (mLabelTimer >= mReadyLabelOffScreen)
			{
				StartStage();

				// activate player
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mPlayerHit)
	{
		if (QuickSDL::InputManager::Instance()->KeyPressed(SDL_SCANCODE_H))
		{
			mPlayer->IsHit();
			mSideBar->SetShips(mPlayer->Lives());
			mPlayerHit = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mBackgroundStar->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mPlayer->Lives() > 0)
		{
			if (mPlayerRespawnTimer == 0.0f)
			{
				mPlayer->Visible(false);
			}

			mPlayerRespawnTimer += mTimer->DeltaTime();

			if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
			{
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mBackgroundStar->Scroll(true);
			}
		}
		else
		{
			if (mGameOverTimer == 0.0f)
			{
				mPlayer->Visible(false);
			}

			mGameOverTimer += mTimer->DeltaTime();

			if (mGameOverTimer >= mGameOverDelay)
			{
				mCurrentState = LEVEL_STATES::gameover;
			}
		}
	}
}

Level::LEVEL_STATES Level::State()
{
	return mCurrentState;
}

void Level::Update()
{
	if (!mStageStarted)
	{
		HandleStartLabels();
	}
	else
	{
		HandleCollisions();

		if (mPlayerHit)
		{
			HandlePlayerDeath();
		}

		else
		{
			if (QuickSDL::InputManager::Instance()->KeyPressed(SDL_SCANCODE_F))
			{
				mCurrentState = LEVEL_STATES::finished;
			}
		}
		
	}
}

void Level::Render()
{
	if (!mStageStarted)
	{
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer <= mStageLabelOffScreen)
		{
			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer <= mReadyLabelOffScreen)
		{
			mReadyLabel->Render();
		}
	}
	else
	{
		if (mPlayerHit)
		{
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
			{
				mReadyLabel->Render();
			}

			if (mGameOverTimer > mGameOverOnScreen)
			{
				mGameOverLabel->Render();
			}
		}
	}
}

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
}

void Level::StartStage()
{
	mStageStarted = true;
}

void Level::Update()
{
	if (!mStageStarted)
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
}

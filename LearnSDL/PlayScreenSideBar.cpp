#include "PlayScreenSideBar.h"

PlayScreenSideBar::PlayScreenSideBar()
{
	mTimer = QuickSDL::Timer::Instance();
	mAudioManager = QuickSDL::AudioManager::Instance();

	mBackground = std::shared_ptr<QuickSDL::Texture>(new QuickSDL::Texture("Black.png"));

	mBackground->Parent(this);
	mBackground->Pos(QuickSDL::Vector2(45.0f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.4f));
	mBackground->Scale(QuickSDL::Vector2(3.0f, 10.0f));

	mHighLabel = std::shared_ptr<QuickSDL::Texture>(new QuickSDL::Texture("HIGH", "myFont.ttf", 32, { 150,0,0 }));
	mHighLabel->Parent(this);
	mHighLabel->Pos(QuickSDL::Vector2(15.0f, 32));

	mScoreLabel = std::shared_ptr<QuickSDL::Texture>(new QuickSDL::Texture("SCORE", "myFont.ttf", 32, { 150,0,0 }));
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(QuickSDL::Vector2(15.0f, 64.0f));

	mHighScoreBoard = std::make_shared<ScoreBoard>();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(QuickSDL::Vector2(70.0f, 100.0f));
	
	mPlayerOneLabel = std::shared_ptr<QuickSDL::Texture>(new QuickSDL::Texture("1UP", "myFont.ttf", 32, { 150,0,0 }));
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(QuickSDL::Vector2(-40.0f, 145.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mIsPlayerOneVisible = true;

	mPlayerOneScore = std::make_shared<ScoreBoard>();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(QuickSDL::Vector2(70.0f, 175.0f));

	mShips = new QuickSDL::GameEntity();
	mShips->Parent(this);
	mShips->Pos(QuickSDL::Vector2(-40.0f, 300.0f));

	for (size_t i = 0; i < MAX_SHIP_TEXTURES; i++)
	{
		mShipTextures[i] = new QuickSDL::Texture("Ship.png");
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(QuickSDL::Vector2(62.0f * (i % 3), 70.0f * (i / 3)));
	}

	mTotalShipsLabel = new ScoreBoard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Pos(QuickSDL::Vector2(140.0f, 75.0f));

	mFlags = new QuickSDL::GameEntity();
	mFlags->Parent(this);
	mFlags->Pos(QuickSDL::Vector2(-50.f, 480.f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.5f;
}

PlayScreenSideBar::~PlayScreenSideBar()
{
	mTimer = NULL;
	mAudioManager = NULL;

	delete mShips;
	mShips = NULL;

	for (size_t i = 0; i < MAX_SHIP_TEXTURES; i++)
	{
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}

	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;

	delete mFlags;
	mFlags = NULL;

	ClearFlags();
}

void PlayScreenSideBar::ClearFlags()
{
	for (QuickSDL::Texture* mFlagTexture : mFlagTextures)
	{
		delete mFlagTexture;
		mFlagTexture = NULL;
	}
	mFlagTextures.clear();
}

void PlayScreenSideBar::AddNextFlag()
{
	if (mRemainingLevels >= 50)
	{
		AddFlag("50LevelFlag.png", 62.0f, 50);
	}
	else if (mRemainingLevels >= 30)
	{
		AddFlag("30LevelFlag.png", 62.0f, 30);
	}
	else if (mRemainingLevels >= 20)
	{
		AddFlag("20LevelFlag.png", 62.0f, 20);
	}
	else if (mRemainingLevels >= 10)
	{
		AddFlag("10LevelFlag.png", 54.0f, 10);
	}
	else if (mRemainingLevels >= 5)
	{
		AddFlag("5LevelFlag.png", 30.0f, 5);
	}
	else 
	{
		AddFlag("1LevelFlag.png", 30.0f, 1);
	}
}

void PlayScreenSideBar::AddFlag(const std::string& filename, float width, int value)
{
	if (mFlagTextures.size() > 0)
	{
		mFlagXOffset += width * 0.5f;
	}
	

	mRemainingLevels -= value;
	mFlagTextures.push_back(new QuickSDL::Texture(filename));
	mFlagTextures.back()->Parent(mFlags);
	mFlagTextures.back()->Pos(QuickSDL::VEC2_Right * mFlagXOffset);
	mFlagXOffset += width * 0.5f;

	// play sound
	mAudioManager->PlaySFX("FlagSound.wav");
}

void PlayScreenSideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlayScreenSideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlayScreenSideBar::SetShips(int ships)
{
	mTotalShips = ships;

	if (ships > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Score(ships);
	}
}

void PlayScreenSideBar::SetLevel(int level)
{
	ClearFlags();

	mRemainingLevels = level;

	mFlagXOffset = 0.0f;
}

void PlayScreenSideBar::Update()
{
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval)
	{
		mIsPlayerOneVisible = !mIsPlayerOneVisible;
		mBlinkTimer = 0.0f;
	}

	if (mRemainingLevels > 0)
	{
		mFlagTimer += mTimer->DeltaTime();

		if (mFlagTimer >= mFlagInterval)
		{
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlayScreenSideBar::Render()
{
	mBackground->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();
	if (mIsPlayerOneVisible)
	{
		mPlayerOneLabel->Render();
	}

	mPlayerOneScore->Render();

	for (size_t i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; i++)
	{
		mShipTextures[i]->Render();
	}

	if (mTotalShips > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Render();
	}

	for (QuickSDL::Texture* mFlagTexture : mFlagTextures)
	{
		mFlagTexture->Render();
	}
}

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

void PlayScreenSideBar::Update()
{
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval)
	{
		mIsPlayerOneVisible = !mIsPlayerOneVisible;
		mBlinkTimer = 0.0f;
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
		mTotalShipsLabel->Render();
}

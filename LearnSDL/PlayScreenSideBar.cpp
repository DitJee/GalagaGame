#include "PlayScreenSideBar.h"

PlayScreenSideBar::PlayScreenSideBar()
{
	mTimer = QuickSDL::Timer::Instance();
	mAudioManager = QuickSDL::AudioManager::Instance();

	mBackground = new QuickSDL::Texture("Black.png");

	mBackground->Parent(this);
	mBackground->Pos(QuickSDL::Vector2(45.0f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.4f));
	mBackground->Scale(QuickSDL::Vector2(3.0f, 10.0f));

	mHighLabel = new QuickSDL::Texture("HIGH", "myFont.ttf", 32, { 150,0,0 });
	mHighLabel->Parent(this);
	mHighLabel->Pos(QuickSDL::Vector2(15.0f, 32));

	mScoreLabel = new QuickSDL::Texture("SCORE", "myFont.ttf", 32, { 150,0,0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(QuickSDL::Vector2(15.0f, 64.0f));

	mHighScoreBoard = new ScoreBoard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(QuickSDL::Vector2(70.0f, 100.0f));
	
	mPlayerOneLabel = new QuickSDL::Texture("1UP", "myFont.ttf", 32, { 150,0,0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(QuickSDL::Vector2(-40.0f, 145.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mIsPlayerOneVisible = true;

	mPlayerOneScore = new ScoreBoard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(QuickSDL::Vector2(70.0f, 175.0f));
}

PlayScreenSideBar::~PlayScreenSideBar()
{
	mTimer = NULL;
	mAudioManager = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighLabel;
	mHighLabel = NULL;

	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreBoard;
	mHighScoreBoard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
}

void PlayScreenSideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlayScreenSideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
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
}

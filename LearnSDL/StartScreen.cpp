#include "StartScreen.h"
#include <cstdint>
#include <algorithm>
#include <iostream>
StartScreen::StartScreen()
{
	mInputManger = QuickSDL::InputManager::Instance();
#pragma region Top bar entities
	// Top bar entities
	QuickSDL::Vector2 topBarPos = QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mTopBar = new QuickSDL::GameEntity(topBarPos.x, topBarPos.y);

	// player one
	mPlayerOne = new QuickSDL::Texture("1UP", "myFont.ttf", 32, { 200,0,0 });

	// player two
	mPlayerTwo = new QuickSDL::Texture("2UP", "myFont.ttf", 32, { 200,0,0 });

	// high score
	mHighScore = new QuickSDL::Texture("High Score", "myFont.ttf", 32, { 200,0,0 });

	// assign to top bar
	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHighScore->Parent(mTopBar);

	mPlayerOne->Pos(QuickSDL::Vector2(-QuickSDL::Graphics::SCREEN_WIDTH * 0.25, 0.0f));
	mPlayerTwo->Pos(QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.25, 0.0f));
	mHighScore->Pos(QuickSDL::VEC2_ZERO);

	// assign top bar to start screen
	mTopBar->Parent(this);
#pragma endregion

#pragma region Logo
	mLogo = new QuickSDL::Texture("Logo.png", 0,0,400,205);

	mAnimatedLogo = new QuickSDL::AnimatedTexture("Logo.png", 20, 29, 385-20, 209-30, 3, 0.5f, QuickSDL::AnimatedTexture::ANIM_DIR::vertical);

	QuickSDL::Vector2 logoPos = QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.5f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.3f);
	mLogo->Pos(logoPos);
	mLogo->Parent(this); 

	mAnimatedLogo->Pos(logoPos);
	mAnimatedLogo->Parent(this);
#pragma endregion

#pragma region Play Mode Entities

	// play mode Entities
	QuickSDL::Vector2 playModePos = QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH * 0.5f, QuickSDL::Graphics::SCREEN_HEIGHT * 0.6f);

	// PlayModes
	mPlayModes = new QuickSDL::GameEntity(playModePos.x, playModePos.y);

	// single player mode
	mSinglePlayerMode = new QuickSDL::Texture("Single Player", "myFont.ttf", 32, { 230,230,230 });

	// duo player mode
	mDuoPlayerMode = new QuickSDL::Texture("Duo Player", "myFont.ttf", 32, { 230,230,230 });

	// cursor 
	mCursor = new QuickSDL::Texture("Cursor.png");

	// assign to play modes
	mSinglePlayerMode->Parent(mPlayModes);
	mDuoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mSinglePlayerMode->Pos(QuickSDL::Vector2(0.0f, -35.0f));
	mDuoPlayerMode->Pos(QuickSDL::Vector2(0.0f, 35.0f));
	mCursor->Pos(QuickSDL::Vector2(-170.f, -35.0f));

	// assign to start screen
	mPlayModes->Parent(this);
#pragma endregion

#pragma region Cursor movement
	mCursorStartPos = mCursor->Pos(QuickSDL::Texture::SPACE::local);
	mCursorOffset = QuickSDL::Vector2(0.f, 70.0f);
	mSelectedMode = 0;
#pragma endregion


#pragma region Bottom Bar Entities
	QuickSDL::Vector2 BottomBarPos = QuickSDL::Vector2(QuickSDL::Graphics::SCREEN_WIDTH *0.5f, QuickSDL::Graphics::SCREEN_HEIGHT*0.8f);
	mBottomBar = new QuickSDL::GameEntity(BottomBarPos.x, BottomBarPos.y);

	mTOAD = new QuickSDL::Texture("TOAD Studio", "myFont.ttf", 36, { 200,0,0 });
	mDates = new QuickSDL::Texture("02/02/2022", "myFont.ttf", 36, { 230,230,230 });
	mCPR = new QuickSDL::Texture("Copy Righted", "myFont.ttf", 36, { 230,230,230 });

	mTOAD->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mCPR->Parent(mBottomBar);

	mTOAD->Pos(QuickSDL::Vector2(-300.0f, 0.0f));
	mDates->Pos(QuickSDL::Vector2(0.0f, 0.0f));
	mCPR->Pos(QuickSDL::Vector2(300.0f, 0.0f));

	mBottomBar->Parent(this);

#pragma endregion

#pragma region Animation
	// screen animation

	// start pos
	mAnimationStartPos = QuickSDL::Vector2(0, QuickSDL::Graphics::SCREEN_HEIGHT);

	// end pos
	mAnimationEndPos = QuickSDL::VEC2_ZERO;

	// period
	mAnimationTotalTime = 5.0f;

	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	mTimer = QuickSDL::Timer::Instance();

	// set initial starting position
	this->Pos(mAnimationStartPos);
#pragma endregion

}

StartScreen::~StartScreen()
{
	delete mTopBar;
	delete mPlayerOne;
	delete mPlayerTwo;
	delete mHighScore;

	delete mLogo;
	delete mAnimatedLogo;

	delete mPlayModes;
	delete mSinglePlayerMode;
	delete mDuoPlayerMode;
	delete mCursor;

	delete mBottomBar;
	delete mTOAD;
	delete mDates;
	delete mCPR;

	mTopBar    = NULL;
	mPlayerOne = NULL;
	mPlayerTwo = NULL;
	mHighScore = NULL;

	mLogo = NULL;
	mAnimatedLogo = NULL;

	mPlayModes		  = NULL;
	mSinglePlayerMode = NULL;
	mDuoPlayerMode	  = NULL;
	mCursor           = NULL;

	mBottomBar = NULL;
	mTOAD = NULL;
	mDates = NULL;
	mCPR = NULL;
}

void StartScreen::ChangeSelectedMode(int changedMode)
{
	mSelectedMode += changedMode;
	
	mSelectedMode = std::clamp(mSelectedMode, 0, 1);

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
	
}

void StartScreen::Update() 
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		this->Pos(QuickSDL::Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
		}
	}
	else
	{
		mAnimatedLogo->Update();

		// input
		if (mInputManger->KeyPressed(SDL_SCANCODE_DOWN))
		{
			ChangeSelectedMode(1);
		}
		else if (mInputManger->KeyPressed(SDL_SCANCODE_UP))
		{
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render()
{
	mTopBar->Render();
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHighScore->Render();

	if (mAnimationDone) mAnimatedLogo->Render();
	else mLogo->Render();


	mPlayModes->Render();
	mSinglePlayerMode->Render();
	mDuoPlayerMode->Render();
	mCursor->Render();

	mBottomBar->Render();
	mTOAD->Render();
	mDates->Render();
	mCPR->Render();
}
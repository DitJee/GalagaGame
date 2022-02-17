#pragma once

#include "AnimatedTexture.h"
#include "InputManager.h"

class StartScreen : public QuickSDL::GameEntity
{
private:
	
	// Top bar 
	QuickSDL::GameEntity* mTopBar;
	QuickSDL::Texture* mPlayerOne;
	QuickSDL::Texture* mPlayerTwo;
	QuickSDL::Texture* mHighScore;

	// Logo
	QuickSDL::Texture* mLogo;
	QuickSDL::AnimatedTexture* mAnimatedLogo;

	// Play Mode
	QuickSDL::GameEntity* mPlayModes;
	QuickSDL::Texture* mSinglePlayerMode;
	QuickSDL::Texture* mDuoPlayerMode;
	QuickSDL::Texture* mCursor;

	// cursor movement
	QuickSDL::Vector2 mCursorStartPos;
	QuickSDL::Vector2 mCursorOffset;
	int mSelectedMode;

	// Bottom Bar
	QuickSDL::GameEntity* mBottomBar;
	QuickSDL::Texture* mTOAD;
	QuickSDL::Texture* mDates;
	QuickSDL::Texture* mCPR;

	// Screen Animation Vars
	QuickSDL::Vector2 mAnimationStartPos;
	QuickSDL::Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	QuickSDL::Timer* mTimer;

	// input manager
	QuickSDL::InputManager* mInputManger;

public:
	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int changedMode);

	void Update() override;
	void Render() override;
};
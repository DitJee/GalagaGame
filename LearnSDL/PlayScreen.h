#pragma once

#include "Level.h"


class PlayScreen : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::InputManager* mInputManager;

	BackgroundStar* mBackgroundStar;

	PlayScreenSideBar* mSideBar;

	QuickSDL::AudioManager* mAudioManager;
	
	QuickSDL::Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	bool mLevelStarted;
	int mCurrentStage;

	Level* mLevel;


	Player* mPlayer;
private:

	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	bool GameOver();

	void Update();
	void Render();
};
#pragma once

#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

class PlayScreenSideBar : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::AudioManager* mAudioManager;

	QuickSDL::Texture* mBackground;

	// labels
	QuickSDL::Texture* mHighLabel;
	QuickSDL::Texture* mScoreLabel;

	ScoreBoard* mHighScoreBoard;

	QuickSDL::Texture* mPlayerOneLabel;

	float mBlinkTimer;
	float mBlinkInterval;
	bool mIsPlayerOneVisible;

	ScoreBoard* mPlayerOneScore;

public:
	PlayScreenSideBar();
	~PlayScreenSideBar();

	void SetHighScore(int score);

	void SetPlayerScore(int score);
	
	void Update();
	void Render();
};
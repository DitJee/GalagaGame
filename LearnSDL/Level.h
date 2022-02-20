#pragma once

#include "InputManager.h"
#include "PlayScreenSideBar.h"
#include "BackgroundStar.h"

class Level : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	PlayScreenSideBar* mSideBar;
	BackgroundStar* mBackgroundStar;

	int mStage;
	bool mStageStarted;
	
	float mLabelTimer;

	QuickSDL::Texture* mStageLabel;
	ScoreBoard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	QuickSDL::Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

private:
	void StartStage();

public:

	Level(int stage, PlayScreenSideBar* sideBar);
	~Level();

	void Update();
	void Render();
};
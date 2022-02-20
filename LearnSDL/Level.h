#pragma once


#include "PlayScreenSideBar.h"
#include "BackgroundStar.h"
#include "Player.h"

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

	Player* mPlayer;
private:
	void StartStage();

public:

	Level(int stage, PlayScreenSideBar* sideBar, Player* player);
	~Level();

	void Update();
	void Render();
};
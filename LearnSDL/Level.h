#pragma once


#include "PlayScreenSideBar.h"
#include "BackgroundStar.h"
#include "Player.h"

class Level : public QuickSDL::GameEntity
{
public:
	enum class LEVEL_STATES : Uint8
	{
		running, finished, gameover
	};

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

	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	QuickSDL::Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverOnScreen;

	LEVEL_STATES mCurrentState;
private:
	void StartStage();
	
	void HandleStartLabels();

	void HandleCollisions();

	void HandlePlayerDeath();

public:

	Level(int stage, PlayScreenSideBar* sideBar, Player* player);
	~Level();

	Level::LEVEL_STATES State();

	void Update();
	void Render();
};
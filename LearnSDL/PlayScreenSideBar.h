#pragma once

#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"
#include <memory>

class PlayScreenSideBar : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::AudioManager* mAudioManager;

	std::shared_ptr<QuickSDL::Texture> mBackground;

	// labels
	std::shared_ptr<QuickSDL::Texture> mHighLabel;
	std::shared_ptr<QuickSDL::Texture> mScoreLabel;

	std::shared_ptr<ScoreBoard> mHighScoreBoard;

	std::shared_ptr<QuickSDL::Texture> mPlayerOneLabel;

	float mBlinkTimer;
	float mBlinkInterval;
	bool mIsPlayerOneVisible;

	std::shared_ptr<ScoreBoard> mPlayerOneScore;

	static const int MAX_SHIP_TEXTURES = 5;

	QuickSDL::GameEntity* mShips;
	QuickSDL::Texture* mShipTextures[MAX_SHIP_TEXTURES];
	ScoreBoard* mTotalShipsLabel;
	int mTotalShips;

public:
	PlayScreenSideBar();
	~PlayScreenSideBar();

	void SetHighScore(int score);

	void SetPlayerScore(int score);

	void SetShips(int ships);
	
	void Update();
	void Render();
};
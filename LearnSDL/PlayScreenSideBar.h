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

	QuickSDL::GameEntity* mFlags;
	std::vector<QuickSDL::Texture*> mFlagTextures;
	int mRemainingLevels;
	int mFlagXOffset;
	float mFlagTimer;
	float mFlagInterval;

private:
	void ClearFlags();

	void AddNextFlag();

	void AddFlag(const std::string& filename, float width, int value);

public:
	PlayScreenSideBar();
	~PlayScreenSideBar();

	void SetHighScore(int score);

	void SetPlayerScore(int score);

	void SetShips(int ships);

	void SetLevel(int level);
	
	void Update();
	void Render();
};
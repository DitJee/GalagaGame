#pragma once

#include "InputManager.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"

class Player : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::InputManager* mInputManager;
	QuickSDL::AudioManager* mAudioManager;

	bool mIsVisible;
	bool mIsAnimating;

	int mScore;
	int mLives;

	QuickSDL::Texture* mShip;

	float mMoveSpeed;
	QuickSDL::Vector2 mMoveBound; // min and max dist to player can move

	QuickSDL::AnimatedTexture* mDeathAnimation;

private:
	void HandleMovement();

public:
	Player();
	~Player();

	void Visible(bool isVisible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int score);

	void IsHit();
	
	void Update();
	void Render();

};
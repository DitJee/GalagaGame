#pragma once

#include "InputManager.h"
#include "AnimatedTexture.h"

class Player : public QuickSDL::GameEntity
{
private:
	QuickSDL::Timer* mTimer;
	QuickSDL::InputManager* mInputManager;

	bool mIsVisible;
	bool mIsAnimating;

	int mScore;
	int mLives;

	QuickSDL::Texture* mShip;

	float mMoveSpeed;
	QuickSDL::Vector2 mMoveBound; // min and max dist to player can move

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
	
	void Update();
	void Render();

};
#include "Player.h"

Player::Player()
{
	mTimer = QuickSDL::Timer::Instance();
	mInputManager = QuickSDL::InputManager::Instance();

	mIsVisible = false;
	mIsAnimating = false;

	mScore = 0;
	mLives = 2;

	mShip = new QuickSDL::Texture("PlayerShip.png");
	mShip->Parent(this);
	mShip->Pos(QuickSDL::VEC2_ZERO);

	mMoveSpeed = 300.f;
	mMoveBound = QuickSDL::Vector2(0.f + 25.f, 800.f - 60.f);
}

Player::~Player()
{
	mTimer = NULL;
	mInputManager = NULL;

	delete mShip;
	mShip = NULL;
}

void Player::HandleMovement()
{
	if (mInputManager->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(QuickSDL::VEC2_Right * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-QuickSDL::VEC2_Right * mMoveSpeed * mTimer->DeltaTime());
	}

	QuickSDL::Vector2 pos = Pos(GameEntity::SPACE::local);
	if (pos.x < mMoveBound.x)
	{
		pos.x = mMoveBound.x;
	}
	else if (pos.x > mMoveBound.y)
	{
		pos.x = mMoveBound.y;
	}

	Pos(pos);
}

void Player::Visible(bool isVisible)
{
	mIsVisible = isVisible;
}
bool Player::IsAnimating()
{
	return mIsAnimating;
}
int Player::Score()
{
	return mScore;
}
int Player::Lives()
{
	return mLives;
}
void Player::AddScore(int score)
{
	mScore += score;
}

void Player::Update()
{
	if (mIsAnimating)
	{

	}
	else
	{
		if (Active())
		{
			HandleMovement();
		}
	}
}

void Player::Render()
{
	if (mIsVisible)
	{
		if (mIsAnimating)
		{

		}
		else
		{
			mShip->Render();	

		}
	}
}

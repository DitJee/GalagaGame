#include "Player.h"

Player::Player()
{
	mTimer = QuickSDL::Timer::Instance();
	mInputManager = QuickSDL::InputManager::Instance();
	mAudioManager = QuickSDL::AudioManager::Instance();

	mIsVisible = false;
	mIsAnimating = false;

	mScore = 0;
	mLives = 2;

	mShip = new QuickSDL::Texture("PlayerShip.png");
	mShip->Parent(this);
	mShip->Pos(QuickSDL::VEC2_ZERO);

	mMoveSpeed = 300.f;
	mMoveBound = QuickSDL::Vector2(0.f + 25.f, 800.f - 60.f);

	mDeathAnimation = new QuickSDL::AnimatedTexture("DeathAnim.png", 0,0, 125,128,4,1.0f,QuickSDL::AnimatedTexture::ANIM_DIR::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(QuickSDL::VEC2_ZERO);
	mDeathAnimation->WrapMode(QuickSDL::AnimatedTexture::WRAP_MODE::once);

	for (size_t i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}
}

Player::~Player()
{
	mTimer = NULL;
	mInputManager = NULL;

	delete mShip;
	mShip = NULL;

	mAudioManager = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (size_t i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}
}

void Player::HandleMovement()
{
	if (mInputManager->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(QuickSDL::VEC2_Right * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-QuickSDL::VEC2_Right * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
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

void Player::HandleFiring()
{
	if (mInputManager->KeyPressed(SDL_SCANCODE_X))
	{
		for (size_t i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(Pos());
				mAudioManager->PlaySFX("FireSound.wav");
				break;
			}
		}
	}
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

void Player::IsHit()
{
	mLives--;
	mDeathAnimation->ResetAnimation();
	mIsAnimating = true;
	mAudioManager->PlaySFX("DeathSound.wav");
}

void Player::Update()
{
	if (mIsAnimating)
	{
		mDeathAnimation->Update();
		mIsAnimating = mDeathAnimation->IsAnimating();
	}
	else
	{
		if (Active())
		{
			HandleMovement();
			HandleFiring();
		}
	}

	for (size_t i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Player::Render()
{
	if (mIsVisible)
	{
		if (mIsAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			mShip->Render();	

		}
	}

	for (size_t i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}
}

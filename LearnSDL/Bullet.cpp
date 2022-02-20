#include "Bullet.h"

Bullet::Bullet()
{
	mTimer = QuickSDL::Timer::Instance();

	mSpeed = 800.f;

	mBullet = new QuickSDL::Texture("Bullet.png");
	mBullet->Parent(this);
	mBullet->Pos(QuickSDL::VEC2_ZERO);

	Reload(); // reuse the bullet
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mBullet;
	mBullet = NULL;
}

void Bullet::Fire(QuickSDL::Vector2 position)
{
	this->Pos(position);
	this->Active(true);
}

void Bullet::Reload()
{
	this->Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		Translate(-QuickSDL::VEC2_UP * mSpeed * mTimer->DeltaTime(), GameEntity::SPACE::local);

		QuickSDL::Vector2 pos = this->Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > QuickSDL::Graphics::SCREEN_HEIGHT + OFFSCREEN_BUFFER)
		{
			Reload();
		}
	}
}

void Bullet::Render()
{
	if (Active())
	{
		mBullet->Render();
	}
}

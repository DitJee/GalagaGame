#pragma once

#include "Texture.h"
#include "Timer.h"

class Bullet : public QuickSDL::GameEntity
{
private:
	const int OFFSCREEN_BUFFER = 10;

	QuickSDL::Timer* mTimer;

	float mSpeed;

	QuickSDL::Texture* mBullet;

public:

	Bullet();
	~Bullet();

	void Fire(QuickSDL::Vector2 position);
	void Reload();

	void Update() override;
	void Render() override;
};


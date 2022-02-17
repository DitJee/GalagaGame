#pragma once

#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture
{
public:

	enum class WRAP_MODE :  int
	{
		once = 0,
		loop = 1
	};

	enum class ANIM_DIR :  int
	{
		horizontal = 0,
		vertical = 1
	};

private:

	Timer* mTimer;

	int mStartX;
	int mStartY;

	float mAnimationTimer;
	float mAnimationSpeed;
	float mTimePerFrame; // time for each frame of the anim to be on screen

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimationDirection;

	bool mAnimationDone;

public:

	AnimatedTexture(const std::string& filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);

	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);

	void Update();

};
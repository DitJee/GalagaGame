#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(const std::string& filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	:Texture(filename, x, y, w, h)
{
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDir;

	mAnimationDone = false;

	mWrapMode = WRAP_MODE::loop;
}

AnimatedTexture::~AnimatedTexture()
{
}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void AnimatedTexture::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == WRAP_MODE::loop)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if (mAnimationDirection == ANIM_DIR::horizontal)
		{
			mClippedRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
		}
		else
		{
			mClippedRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}

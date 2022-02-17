#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	// set transform
	mPos.x = x;
	mPos.y = y;

	// set rotation
	mRotation = 0.0f;

	// set active
	mActive = true;

	// set parent
	mParent = NULL;

	// set scale
	mScale = VEC2_ONE;

}

GameEntity::~GameEntity()
{
	mParent = NULL;

}

void GameEntity::Pos(Vector2 pos)
{
	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mPos;
	}

	Vector2 parentScale = mParent->Scale(SPACE::world);

	// account for parent's rotation
	Vector2 parentPos = mParent->Pos(SPACE::world);
	Vector2 ScaledVector = Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y);
	Vector2 newRotation = RotateVector(ScaledVector, mParent->Rotation(SPACE::local));

	Vector2 newPos = parentPos + newRotation;

	return  newPos;
	
}

void GameEntity::Rotation(float rotation)
{
	mRotation = rotation;

	int wholeNumber = (int)rotation % 360;
	float fraction = rotation - (int)rotation;
	rotation = wholeNumber + fraction;

	if (rotation < 0)
	{
		mRotation = 360.0f + rotation;
	}
	else
	{
		mRotation = rotation;
	}

}

float GameEntity::Rotation(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mRotation;
	}

	return mParent->Rotation(SPACE::world) + mRotation;
}

void GameEntity::Scale(Vector2 scale)
{
	mScale = scale;
}

Vector2 GameEntity::Scale(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mScale;
	}

	Vector2 newScale = mParent->Scale(SPACE::world);

	newScale.x *= mScale.x;
	newScale.y *= mScale.y;

	return newScale;
}

void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::Active()
{
	return mActive;
}

void GameEntity::Parent(GameEntity* parent)
{
	// handle NULL
	if (parent == NULL)
	{
		// pass world variables
		mPos = Pos(SPACE::world);
		mRotation = Rotation(SPACE::world);
		mScale = Scale(SPACE::world);
	}
	else
	{
		// if we alreay have the parent
		if (mParent != NULL)
		{
			// remove the parent
			Parent(NULL);
		}
		// and set new parent

		// handle the position
		Vector2 defaultVector(Pos(SPACE::world) - parent->Pos(SPACE::world));
		mPos = RotateVector(defaultVector, -parent->Rotation(SPACE::world));

		// handle scaling
		Vector2 parentScale = parent->Scale(SPACE::world);
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		// handle world rotation
		mRotation -= parent->Rotation(SPACE::world);

		// world scale
		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);


	}

	mParent = parent;
}

GameEntity* GameEntity::Parent()
{
	return mParent;
}

void GameEntity::Translate(Vector2 vec)
{
	mPos += vec;
}

void GameEntity::Rotate(float angle)
{
	mRotation += angle;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}
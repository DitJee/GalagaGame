#pragma once
#include "MathHelper.h"
class GameEntity
{
public:
	enum class SPACE :unsigned int
	{
		local = 0,
		world = 1
	};

private:

	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	bool mActive; // to tell if the obj is active or not
	GameEntity* mParent; // use to link obj together

public:
	GameEntity(float x = 0.0f, float y = 0.0f );
	~GameEntity();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = SPACE::world);

	void Rotation(float rotation);
	float Rotation(SPACE space = SPACE::world);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = SPACE::world);

	void Active(bool active);
	bool Active(); 

	void Parent(GameEntity* parent);
	GameEntity* Parent();

	void Translate(Vector2 vec);

	void Rotate(float angle);

	virtual void Update();
	virtual void Render();

};
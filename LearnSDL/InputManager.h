#pragma once

#include <SDL.h>
#include <string.h>
#include "MathHelper.h"

class InputManager
{
public:
	enum class MOUSE_BUTTONS : Uint8
	{
		left    = 0,
		right   = 1,
		middle  = 2,
		back    = 3,
		forward = 4
	};

private:
	static InputManager* sInstance;

	const Uint8* mKeyBoardState;
	Uint8* mPrevKeyBoardState;
	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;

	int mMousePosX;
	int mMousePosY;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTONS button);
	bool MouseButtonPressed(MOUSE_BUTTONS button);
	bool MouseButtonReleased(MOUSE_BUTTONS button);

	Vector2 MousePosition();

	void Update();
	void UpdatePrevInput();

private:
	InputManager();
	~InputManager();

};
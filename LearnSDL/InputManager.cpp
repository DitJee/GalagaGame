#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager();

	}

	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

InputManager::InputManager()
{
	mKeyBoardState = SDL_GetKeyboardState(&mKeyLength);

	// init prev kb state
	mPrevKeyBoardState = new Uint8[mKeyLength];

	// pass cur to prev kb state
	memcpy(mPrevKeyBoardState, mKeyBoardState, mKeyLength);
}

InputManager::~InputManager()
{
	delete[] mPrevKeyBoardState;
	mPrevKeyBoardState = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeyBoardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
	
	return !mPrevKeyBoardState[scanCode] && mKeyBoardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
	return mPrevKeyBoardState[scanCode] && !mKeyBoardState[scanCode];
}

bool InputManager::MouseButtonDown(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTONS::left:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTONS::right:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTONS::middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTONS::back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTONS::forward:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}
	return (mMouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTONS::left:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTONS::right:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTONS::middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTONS::back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTONS::forward:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}
	return !(mPrevMouseState & mask) && (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case MOUSE_BUTTONS::left:
		mask = SDL_BUTTON_LMASK;
		break;

	case MOUSE_BUTTONS::right:
		mask = SDL_BUTTON_RMASK;
		break;

	case MOUSE_BUTTONS::middle:
		mask = SDL_BUTTON_MMASK;
		break;

	case MOUSE_BUTTONS::back:
		mask = SDL_BUTTON_X1MASK;
		break;

	case MOUSE_BUTTONS::forward:
		mask = SDL_BUTTON_X2MASK;
		break;

	default:
		break;
	}
	return (mPrevMouseState & mask) && !(mMouseState & mask);
}

Vector2 InputManager::MousePosition()
{

	return Vector2((float)mMousePosX, (float)mMousePosY);
}

void InputManager::Update()
{
	mMouseState = SDL_GetMouseState(&mMousePosX, &mMousePosY);
}

void InputManager::UpdatePrevInput()
{
	memcpy(mPrevKeyBoardState, mKeyBoardState, mKeyLength);
	mPrevMouseState = mMouseState;
}

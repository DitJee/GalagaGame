#pragma once
// *********************************************
// Game manager will init everything in the game
// *********************************************


#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
class GameManager 
{
private:
	static GameManager* sInstance;

	bool mQuit;

	Graphics* mGraphics;

	SDL_Event mEvents; // pull all events in window

	Timer* mTimer;

	const int FRAME_RATE = 60;

	AssetManager* mAssetManager;

	InputManager* mInputManager;

	Texture* mAnimatedTexture;

	Texture* mText2;

	AudioManager* mAudioManager;

public:

	static GameManager* Instance();
	static void Release();

	void Run();

private:

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();
};
#pragma once
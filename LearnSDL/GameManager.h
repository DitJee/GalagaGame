#pragma once
// *********************************************
// Game manager will init everything in the game
// *********************************************


#include "AudioManager.h"
#include "ScreenManager.h"

namespace QuickSDL {


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

		AudioManager* mAudioManager;

		ScreenManager* mScreenMananger;

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
}
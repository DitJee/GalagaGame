#include "GameManager.h"

namespace QuickSDL {


	GameManager* GameManager::sInstance = NULL;

	GameManager* GameManager::Instance()
	{
		if (sInstance == NULL)
		{
			sInstance = new GameManager();
		}

		return sInstance;
	}

	void GameManager::Release()
	{
		delete sInstance;
		sInstance = NULL;

	}

	GameManager::GameManager()
	{
		mQuit = false;
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialize())
		{
			mQuit = true;
		}

		// init timer
		mTimer = Timer::Instance();

		// init asset manager
		mAssetManager = AssetManager::Instance();

		// init input manager
		mInputManager = InputManager::Instance();

		// init Audio manager
		mAudioManager = AudioManager::Instance();

		// init Start screen
		mStartScreen = new StartScreen();
	}

	GameManager::~GameManager()
	{
		// delete asset manager
		mAssetManager->Release();
		mAssetManager = NULL;

		// release graphics
		Graphics::Release();
		mGraphics = NULL;

		// release timer
		mTimer->Release();
		mTimer = NULL;

		// delete input manager
		mInputManager->Release();
		mInputManager = NULL;

		// delete audio menager
		mAudioManager->Release();
		mAudioManager = NULL;

		// delete start screen
		delete mStartScreen;
		mStartScreen = NULL;
	}

	void GameManager::EarlyUpdate()
	{
		// update KB input
		mInputManager->Update();
	}

	void GameManager::Update()
	{
		mStartScreen->Update();
	}

	void GameManager::LateUpdate()
	{
		mInputManager->UpdatePrevInput();

		mTimer->Reset();
	}


	void GameManager::Render()
	{
		mGraphics->ClearBackBuffer();

		mStartScreen->Render();

		mGraphics->Render();
	}

	void GameManager::Run()
	{
		while (!mQuit)
		{

			mTimer->Update();

			while (SDL_PollEvent(&mEvents) != 0)
			{
				if (mEvents.type == SDL_QUIT)
				{
					mQuit = true;
				}

			}

			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
			{
				EarlyUpdate();
				Update();
				LateUpdate();
				Render();

			}
		}
	}
}
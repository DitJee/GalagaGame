#include "GameManager.h"
#include <time.h>

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
		srand(time(0));

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

		// init ScreenMananger
		mScreenMananger = ScreenManager::Instance();

	}

	GameManager::~GameManager()
	{
		// delete mScreenMananger
		mScreenMananger->Release();
		mScreenMananger = NULL;

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

	
	}

	void GameManager::EarlyUpdate()
	{
		// update KB input
		mInputManager->Update();
	}

	void GameManager::Update()
	{
		mScreenMananger->Update();
	}

	void GameManager::LateUpdate()
	{
		mInputManager->UpdatePrevInput();

		mTimer->Reset();
	}


	void GameManager::Render()
	{
		mGraphics->ClearBackBuffer();

		mScreenMananger->Render();

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
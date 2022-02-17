#include "GameManager.h"


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

	mAnimatedTexture = new Texture("Hello World!", "myFont.ttf", 72, {255, 0, 0});

	mAnimatedTexture->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mText2  = new Texture("Hello World!", "myFont.ttf", 72, { 255, 0, 0 });

	mText2->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.51f));

	//mText2->Scale(Vector2(0.5f, 1.5f));

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

	// delete texture
	delete mAnimatedTexture;
	mAnimatedTexture = NULL;

	// delete audio menager
	mAudioManager->Release();
	mAudioManager = NULL;

	delete mText2;
	mText2 = NULL;
}

void GameManager::EarlyUpdate()
{
	// update KB input
	mInputManager->Update();
}

void GameManager::Update()
{
	mAnimatedTexture->Rotate(10 * mTimer->DeltaTime());
	// play SFX
	if (mInputManager->KeyPressed(SDL_SCANCODE_W))
	{
		mText2->Parent(mAnimatedTexture);
	}

	if (mInputManager->KeyPressed(SDL_SCANCODE_S))
	{
		mText2->Parent(NULL);
	}

	if (mInputManager->MouseButtonPressed(InputManager::MOUSE_BUTTONS::middle))
	{

		mAudioManager->PlaySFX("sword-clash.wav", 0);
	}
	if (mInputManager->MouseButtonReleased(InputManager::MOUSE_BUTTONS::left))
	{
		mAudioManager->PlaySFX("sword-clash.wav", 0);
	}

	//mAnimatedTexture->Update();
	//mText2->Update();
	//mText2->Rotate(10 * mTimer->DeltaTime());
	mText2->Scale(mText2->Scale(GameEntity::SPACE::world) + Vector2(0.001f, 0.01f));
	//printf("Delta time: %f \n", mTimer->DeltaTime());
}

void GameManager::LateUpdate()
{
	mInputManager->UpdatePrevInput();

	mTimer->Reset();
}


void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	// draw texture
	mAnimatedTexture->Render();
	mText2->Render();

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
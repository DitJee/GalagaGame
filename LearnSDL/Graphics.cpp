#include "Graphics.h"

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Graphics();

	}

	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = NULL;
	sInitialized = false;
}

bool Graphics::Initialize()
{
	return sInitialized;
}

Graphics::Graphics()
{
	mBackBuffer = NULL;

	sInitialized = Init();
}

Graphics::~Graphics()
{
	// TODO: clear all vars
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL init error %s \n", SDL_GetError());

		return false;
	}

	// if no error, create window
	mWindow = SDL_CreateWindow("LEARNSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (mWindow == NULL)
	{
		printf("Window creation error %s \n", SDL_GetError());
		return false;
	}

	// get renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	if (mRenderer == NULL)
	{
		printf("Renderer creation error %s \n", SDL_GetError());
		return false;
	}

	// set draw color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_PNG;

	if (!(IMG_Init(flags) & flags))
	{
		printf("IMG Initialization Error %s \n", IMG_GetError());
		return false;
	}

	// init  font
	if (TTF_Init() == -1)
	{
		printf("TTF Initialization Error %s \n", TTF_GetError());
		return false;
	}

	// get back buffer
	mBackBuffer = SDL_GetWindowSurface(mWindow);

	return true;
}

SDL_Texture* Graphics::LoadTexture(const std::string& path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str()); // convert to constant char pointer
	
	if (surface == NULL)
	{
		printf("IMG load Error %s using path %s \n", IMG_GetError(), path.c_str());

		return texture;
	}

	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (texture == NULL)
	{
		printf("Create texture Error %s \n", SDL_GetError());

		return texture;
	}

	SDL_FreeSurface(surface);

	return texture;

}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);

}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(mRenderer, texture, clip, rend, angle, NULL, flip);
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, const std::string& text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	
	if (surface == NULL)
	{
		printf("Text Render Error %s \n", TTF_GetError());
		return NULL;
	}

	// convert surface to texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer,surface);
	if (tex == NULL)
	{
		printf("Text Texture creation Error %s \n", SDL_GetError());
		return NULL;
	}

	// free the surface resource
	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::Render()
{
	//SDL_UpdateWindowSurface(mWindow);
	SDL_RenderPresent(mRenderer);
}
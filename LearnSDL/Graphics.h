#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class Graphics
{
public :
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

private:
	static Graphics* sInstance;
	static bool sInitialized; // true if init correctly

	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;

public:

	static Graphics* Instance(); // return the instance
	static void Release();
	static bool Initialize();

	void Render();

	SDL_Texture* LoadTexture(const std::string& path);

	void ClearBackBuffer(); // called every frame to clear the canvas

	void DrawTexture(SDL_Texture* texture, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture* CreateTextTexture(TTF_Font* font, const std::string& text, SDL_Color color);

private:

	Graphics();
	~Graphics();

	bool Init();


};


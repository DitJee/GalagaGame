#pragma once

#include "Texture.h"
#include <vector>

class ScoreBoard : public QuickSDL::GameEntity
{
private:

	std::vector<QuickSDL::Texture*> mScore;

	SDL_Color mColor;

public:

	ScoreBoard();
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	void Score(int score);
	
	void Render();

private:

	void ClearBoard();
};
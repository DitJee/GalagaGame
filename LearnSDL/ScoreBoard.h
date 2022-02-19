#pragma once

#include "Texture.h"
#include <vector>

class ScoreBoard : public QuickSDL::GameEntity
{
private:

	std::vector<QuickSDL::Texture*> mScore;

public:

	ScoreBoard();
	~ScoreBoard();

	void Score(int score);
	
	void Render();

private:

	void ClearBoard();
};
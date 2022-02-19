#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	Score(0);
}

ScoreBoard::~ScoreBoard()
{
	ClearBoard();
}

void ScoreBoard::Score(int score)
{
	ClearBoard();

	if (score == 0)
	{
		// loop twice to add 00 as a score
		for (size_t i = 0; i < 2; i++)
		{
			mScore.push_back(new QuickSDL::Texture("0", "myFont.ttf", 32, { 230,230,230 }));

			mScore[i]->Parent(this);
			mScore[i]->Pos(QuickSDL::Vector2(-32.0f * i, 0.0f));
		}
	}
	else
	{
		std::string score_str = std::to_string(score);

		for (size_t i = 0; i <= score_str.length()-1; i++)
		{
			mScore.push_back(new QuickSDL::Texture(score_str.substr(i,1), "myFont.ttf", 32, { 230,230,230 }));

			mScore[i]->Parent(this);
			mScore[i]->Pos(QuickSDL::Vector2(-32.0f * (score_str.length() - 1 - i), 0.0f));

		}
	}
}

void ScoreBoard::Render()
{
	for (QuickSDL::Texture* Score : mScore)
	{
		Score->Render();
	}
}

void ScoreBoard::ClearBoard()
{
	for (size_t i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

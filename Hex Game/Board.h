#pragma once
#include <string>
#include <vector>

#include "Game.h"
class Board
{
public:
	Board();
	~Board();
	void DrawBoard();
	bool AddPoint(std::string &input, Game::PlayerType &playerType);
	bool DeletePreviousPoint(int &playerNumber);
	void pieRule();
private:
	char** board;
	const static int height = 11;
	const static int width = 11;
	int pseudoLeft = 0;
	int pseudoRight = width - 1;
	int pseudoTop = height - 1;
	int pseudoBottom = 0;

	Game::PlayerType playerType = Game::PlayerType::HUMAN;

	Game::PlayerType curPlayerType = Game::PlayerType::HUMAN;

	void PrepareBoard();
	bool isConnected(int playerNumber, int x, int y);

	//vector< vector<int> > nodes;
};


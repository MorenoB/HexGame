#pragma once
#include <string>
#include <vector>

class Board
{
public:
	Board();
	~Board();

	enum PlayerType { HUMAN, AI };

	void DrawBoard();
	bool AddPoint(std::string &input, PlayerType &playerType);
	bool DeletePreviousPoint(int &playerNumber);
	void pieRule();
private:
	char** board;
	const static int height = 11;
	const static int width = 11;
	bool checkboard[width][height];
	int pseudoLeft = 0;
	int pseudoRight = width - 1;
	int pseudoTop = height - 1;
	int pseudoBottom = 0;

	PlayerType playerType = PlayerType::HUMAN;

	PlayerType curPlayerType = PlayerType::HUMAN;

	void PrepareBoard();
	void ClearCheckboard();
	bool IsConnected(int playerNumber, int x, int y);
	bool IsConnectedLeftToRight();
	bool IsConnectedTopToDown();
	bool RecursivelyCheckTopToDown(int x, int y);
	bool RecursivelyCheckLeftToRight(int x, int y);
};


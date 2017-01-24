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
	int pseudoLeft = 0;
	int pseudoRight = width - 1;
	int pseudoTop = height - 1;
	int pseudoBottom = 0;

	PlayerType playerType = PlayerType::HUMAN;

	PlayerType curPlayerType = PlayerType::HUMAN;

	void PrepareBoard();
	bool isConnected(int playerNumber, int x, int y);

	//vector< vector<int> > nodes;
};


#pragma once
#include <string>
#include <vector>
#include "Board.h"

class Game
{
public:
	void Start();
	
private:
	int currentPlayer = 1;
	int turnCounter = 1;
	const int C_AI_MAXLOOPS = 500;
	
	Board board;
	Board::PlayerType playerType = Board::PlayerType::HUMAN;
	std::string currentInput;

	std::vector<std::string> playerMoves1;
	std::vector<std::string> playerMoves2;

	void makeTurn();
	void doTurn(std::string location);
	void deleteTurn();
	void doPierule();
	void randomAI();
	void RedrawBoard();
	void WaitForInput();
	bool isValidInput(std::string &input);
	void Update();
};
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <regex>
#include <stdlib.h>
#include <thread>
#include <mutex>

#include "Board.h"

using namespace std;

class Game
{
public:
	void Start();
	
private:
	bool aiWorkerThreadIsRunning = true;
	int currentPlayer = 1;
	int turnCounter = 1;
	const int C_AI_MAXLOOPS = 500;
	
	Board board;
	Board::PlayerType playerType = Board::PlayerType::HUMAN;
	string currentInput;

	mutex mutex;

	vector<string> playerMoves1;
	vector<string> playerMoves2;
	vector<string> randomAIPoints;

	void makeTurn();
	void doTurn(string location);
	void deleteTurn();
	void doPierule();
	void randomAI();
	void ChooseRandomPointWorkerThread();
	void RedrawBoard();
	void WaitForInput();
	void Update();

	bool isValidInput(string &input);

};
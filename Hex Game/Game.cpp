//Game.cpp main game loop.
#include "stdafx.h"
#include "game.h"
#include "board.h"
#include "concol.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <regex>
#include <thread>
#include <stdlib.h>

using namespace std;
using namespace eku;


/* Game functions:
+ Mostly Acts like a controller.
+ Game update loop is in here.
+ Checks the input if its valid.
+ Keeps track of whose turn it is.
*/


// Member functions definitions including constructor
Game::Game(void)
{
	board = new Board();
}

void Game::Start()
{
	board->DrawBoard();
	Update();
}



void Game::Update()
{

	WaitForInput();
	system("cls");
	makeTurn();
	board->DrawBoard();

	playerType = playerType == HUMAN ? AI : HUMAN;

	turnCounter++;
	Update();
}

void Game::WaitForInput()
{
	string input = "";

	//Don't need to wait for input for AI.
	if (playerType == AI)
		return;

	if (turnCounter == 2)
	{
		cout << "Pie rule?" << endl;
	}
	cout << endl;
	cout << endl << "Please give a valid input ";

	settextcolor(blue);
	cout << "Player " << currentPlayer << endl;
	settextcolor(white);

	cin >> input;



	if (!isValidInput(input))
	{
		RedrawBoard();
		cout << "Not a valid input. ('" << input << "')" << endl;
		WaitForInput();
	}

	std::transform(input.begin(), input.end(), input.begin(), toupper);

	//Check if the input is NUMBER+LETTER instead of LETTER+NUMBER, if so, flip them!
	if (isdigit(input[0]))
	{
		char temp = input[0];
		input[0] = input[1];
		input[1] = temp;
	}

	currentInput = input;
	
	return;
}

bool Game::isValidInput(string &input)
{
	if (input.size() != 2 && !(input.size() == 3 && input[2] == '0' || input == "DEL"))
		return false;
	//Check wether the input is numbers or letters only.
	if (std::all_of(input.begin(), input.end(), ::isdigit) || std::regex_match(input, std::regex("^[A-Za-z]+$")))
		return false;

	return true;
}

/* Controller-ish function
IF NOT AI = Provides the player options what do to, for instance; do a turn, delete previous turn or do the pie rule.
IF AI = Calls the randomAI() method which will decide what to do.*/
void Game::makeTurn()
{
	if (playerType == AI)
	{
		if (currentInput == "DEL")
			deleteTurn();
		doTurn(currentInput);
	}
	else
		randomAI();
}

/* Communicates with board.cpp
Deletes the previous added point of this player.*/
void Game::deleteTurn()
{
	board->DeletePreviousPoint(currentPlayer);
}

/* Communicates with board.cpp
Adds a point to the map with the given location.*/
void Game::doTurn(string location)
{
	if (board->AddPoint(location, playerType))
		return;
	else
	{
		cout << "UNABLE TO ADD POINT" << endl;
		RedrawBoard();
	}
	WaitForInput();
	makeTurn();
}

void Game::doPierule()
{
	cout << "Player " << currentPlayer << " executed the pie rule!" << endl;
	board->pieRule();
}

void Game::RedrawBoard()
{
	system("cls");
	board->DrawBoard();
}

/*
Contains all the randomAI decision making.*/
void Game::randomAI()
{
	while (true)
	{
		if (turnCounter == 2)
		{
			doPierule();
			return;
		}

		string randomTurn;

		int i1 = rand() % 10;     // v2 in the range 0 to 11
		int i2 = rand() % 10;     // v2 in the range 0 to 11

		char input1 = "ABCDEFGHIJKLMNOP"[i1 - 1];
		string input = input1 + to_string(i2);

		if (board->AddPoint(input, playerType))
		{
			cout << "AI added point" << input << endl;
			return;
		}
	}
}

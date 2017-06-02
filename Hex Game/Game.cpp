//Game.cpp main game loop.
#include "stdafx.h"
#include "game.h"
#include "board.h"
#include "concol.h"

/* Game functions:
+ Mostly Acts like a controller.
+ Game update loop is in here.
+ Checks the input if its valid.
+ Keeps track of whose turn it is.
*/


// Member functions definitions including constructor
void Game::Start()
{
	board.DrawBoard();

	thread worker(&Game::ChooseRandomPointWorkerThread, this);

	Update();
}



void Game::Update()
{

	WaitForInput();
	system("cls");
	makeTurn();
	board.DrawBoard();

	playerType = playerType == Board::PlayerType::HUMAN ? Board::PlayerType::AI : Board::PlayerType::HUMAN;

	turnCounter++;
	Update();
}

void Game::WaitForInput()
{
	string input = "";

	//Don't need to wait for input for AI.
	if (playerType == Board::PlayerType::AI)
		return;

	if (turnCounter == 2)
	{
		cout << "Pie rule?" << endl;
	}
	cout << endl;
	cout << endl << "Please give a valid input ";

	eku::settextcolor(eku::blue);
	cout << "Player " << currentPlayer << endl;
	eku::settextcolor(eku::white);

	cin >> input;



	if (!isValidInput(input))
	{
		RedrawBoard();
		cout << "Not a valid input. ('" << input << "')" << endl;
		WaitForInput();
		return;
	}

	std::transform(input.begin(), input.end(), input.begin(), ::toupper);

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
	if (playerType == Board::PlayerType::AI)
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
	board.DeletePreviousPoint(currentPlayer);
}

/* Communicates with board.cpp
Adds a point to the map with the given location.*/
void Game::doTurn(string location)
{
	if (board.AddPoint(location, playerType))
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
	board.pieRule();
}

void Game::RedrawBoard()
{
	system("cls");
	board.DrawBoard();
}

/*
Contains all the randomAI decision making.*/
void Game::randomAI()
{
	if (turnCounter == 2)
	{
		doPierule();
		return;
	}

	string randomPoint = randomAIPoints.at(randomAIPoints.size() - 1);
	randomAIPoints.pop_back();


	if (board.AddPoint(randomPoint, playerType))
	{
		cout << "AI added point" << randomPoint << endl;
		return;
	}	

	//We should not exit here!
	cout << "AI was unable to pick a random point!" << endl;
}

void Game::ChooseRandomPointWorkerThread()
{

	while (aiWorkerThreadIsRunning)
	{
		if (randomAIPoints.size() > 1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			continue;
		}

		mutex.try_lock();
		
		int i1 = rand() % 10;     // v2 in the range 0 to 11
		int i2 = rand() % 10;     // v2 in the range 0 to 11

		char input1 = "ABCDEFGHIJKLMNOP"[i1 - 1];
		string input = input1 + to_string(i2);

		if (board.CanPlacePoint(input))
		{
			randomAIPoints.push_back(input);
			mutex.unlock();
		}

		//std::cout << __func__ << ": " << input << '\n';
	}
}

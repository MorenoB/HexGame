#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<std::string> Player1Moves;
vector<std::string> Player2Moves;
vector<int> xValues, yValues;

/* Board functions:
+ Contains the board 2d-array, obviously.
- Updates the board.
+ Outputs the board to screen.
- Checks wether there is a connected line between ends of the board.
+ Can add a point to the board.
+ Can delete a point from the board.
- Can do the pie rule on the board. ( Basicly it inverts the points on the board. )

The Board will only be accessed by the player class, not the game class!
*/

Board::Board()
{
	PrepareBoard();
}

void Board::PrepareBoard()
{
	board = new char*[width];
	for (unsigned i = 0; i < width; i++)
	{
		board[i] = new char[height];
		for (unsigned j = 0; j < height; j++)
		{
			board[i][j] = '.';
		}
	}
}

void Board::DrawBoard()
{
	cout << std::string(3, ' ');
	for (char letter = 'A'; letter <= 'K'; letter++)
		cout << " " << letter;
	cout << endl;
	cout << std::string(3, ' ') << std::string(width * 2 + 1, '_') << endl;
	for (unsigned i = 0; i < width; i++)
	{
		cout << std::string(i, ' ') << i << " | ";
		for (unsigned j = 0; j < height; j++)
		{
			/*if (j % width== 0)
			cout << " " << board[i][j] << endl;*/
			cout << board[i][j] << " ";
		}
		cout << "| " << i << endl;
		//cout << "Board[" << i << "][" << p <<"] = " << board[i][p] << " ";
	}
	cout << string(width + 3, ' ') << std::string(width * 2 + 1, '-') << endl;
	cout << string(width + 3, ' ');
	for (char letter = 'A'; letter <= 'K'; letter++)
		cout << " " << letter;
	cout << endl;

}

bool Board::AddPoint(string &input, PlayerType &playerType)
{
	int letter = input[0] - 65;
	int number = input[1] - '0';
	curPlayerType = playerType;

	if (playerType == 1)
		Player1Moves.push_back(input);
	else
		Player2Moves.push_back(input);

	if (input.size() == 3)
	{
		number = 10;
	}
	if (letter < width && number < height)
	{
		if (board[number][letter] != '.')
		{
			if (playerType != 2)
			cout << "Please repick!" << endl;
			return false;
		}
		if (playerType == 1)
			board[number][letter] = 'x';
		else
			board[number][letter] = 'o';
		cout << endl;
		cout << endl << "Modified Point: " << input[0] << number << " to " << board[number][letter] << endl;
		//if (number == pseudoTop || number == pseudoBottom || letter == pseudoLeft || letter == pseudoRight)
		if (isConnected(curPlayerType, number, letter))
			cout << "CONNECTED PLAYER" << curPlayerType << endl;
		return true;
	}
	else
		cout << "POINT IS OUT OF RANGE! Point: " << input[0] << number << endl;
	return false;
}


bool Board::DeletePreviousPoint(int &playerNumber)
{
	string previousMove;
	if (playerNumber == 1)
	{
		previousMove = Player1Moves.back();
		Player1Moves.pop_back();
	}
	else
	{
		previousMove = Player2Moves.back();
		Player2Moves.pop_back();
	}

	int letter = previousMove[0] - 65;
	int number = previousMove[1] - '0';

	if (previousMove.size() == 3)
	{
		previousMove = 10;
	}
	if (letter < width && number < height)
	{
		board[number][letter] = '.';
		cout << "Modified Point: " << previousMove[0] << number << " to " << board[number][letter] << endl;
		return true;
	}
	else
		cout << "POINT IS OUT OF RANGE! Point: " << previousMove[0] << number << " = " << board[letter][number] << endl;
	return false;
}

bool Board::isConnected(int playerNumber, int x, int y)
{
	char playerIcon;
	if (playerNumber == 1)
		playerIcon = 'x';
	else
		playerIcon = 'o';
	int directions = 4;
	int count = 0;
	for (int i = 0; i < directions; i++)
	{
		count++;
		if (count > 20)
			return false;
		if (board[y][x + 1] == playerIcon)
		{
			if (x + 1 < width && x + 1 == pseudoRight)
				return true;
			/*if (xValues.size() > 0 && x + 1 != xValues.back())
			{*/
			i = 0;
			/*xValues.pop_back();
		}*/
			xValues.push_back(x);
			yValues.push_back(y);
			x++;
		}

		if (y + 1 < height && board[y + 1][x] == playerIcon)
		{
			if (y + 1 == pseudoTop)
				return true;
			/*if (yValues.size() > 0 && y + 1 != yValues.back())
			{*/
			i = 0;
			/*yValues.pop_back();
		}*/
			xValues.push_back(x);
			yValues.push_back(y);
			y++;
		}

		if (x - 1 > 0 && board[y][x - 1] == playerIcon)
		{
			if (x - 1 == pseudoLeft)
				return true;
			/*if (xValues.size() > 0 && x - 1 != xValues.back())
			{*/
			i = 0;
			/*xValues.pop_back();
		}*/
			xValues.push_back(x);
			yValues.push_back(y);
			x--;
		}
		if (y - 1 > 0 && board[y - 1][x] == playerIcon)
		{
			if (y - 1 == pseudoBottom)
				return true;
			/*if (yValues.size() > 0 && y - 1 != yValues.back())
			{*/
			i = 0;
			/*yValues.pop_back();
		}*/
			xValues.push_back(x);
			yValues.push_back(y);
			y--;
		}

		/*
		if (equalCount > 1)
		{
		int xTemp = xValues.back();
		int yTemp = yValues.back();
		xValues.pop_back();
		yValues.pop_back();
		}
		else if (equalCount == 1)
		{
		int xTemp = xValues.back();
		int yTemp = yValues.back();
		xValues.pop_back();
		yValues.pop_back();
		modifiedBoard[xTemp][yTemp] = '.';
		if (xTemp == width || yTemp == height)
		return true;
		}*/
	}
	return false;
}

void Board::pieRule()
{
	for (unsigned i = 0; i < width; i++)
	{
		for (unsigned j = 0; j < height; j++)
		{
			if (board[i][j] == 'x')
			{
				board[i][j] = 'o';
				continue;
			}
			if (board[i][j] == 'o')
			{
				board[i][j] = 'x';
				continue;
			}
		}
	}
	return;
}

Board::~Board()
{
}

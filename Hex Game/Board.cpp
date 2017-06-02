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

bool Board::CanPlacePoint(string &input)
{
	int letter = input[0] - 65;
	int number = input[1] - '0';

	if (board[number][letter] != '.')
	{
		return false;
	}

	return true;
}

bool Board::AddPoint(string &input, PlayerType &playerType)
{
	if (input == "" || input.length() == 0)
		return false;

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
		if (IsConnected(curPlayerType))
			cout << "CONNECTED PLAYER" << curPlayerType << endl;
		return true;
	}
	else
		cout << "POINT IS OUT OF RANGE! Point: " << input[0] << number << endl;
	return false;
}

void Board::ClearCheckboard() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			checkboard[i][j] = false;
		}
	}
}

bool Board::IsConnectedTopToDown() {
	ClearCheckboard();
	for (int x = 0; x < width; x++) {
		if (RecursivelyCheckTopToDown(x, 0))
			return true;
	}
	return false;
}

bool Board::IsConnectedLeftToRight() {
	ClearCheckboard();
	for (int y = 0; y < height; y++) {
		if (RecursivelyCheckLeftToRight(0, y))
			return true;
	}
	return false;
}

bool Board::RecursivelyCheckTopToDown(int x, int y) {

	//Already has checked this path.
	if (checkboard[x][y])
		return false;

	checkboard[x][y] = true;

	//At the end of the width
	if (x == width) {
		return false;
	}

	//Check for correct character.
	if (board[x][y] != 'o')
		return false;
	
	//Has completed top to bottom column.
	if (y == height - 1) {
		return true;
	}

	//Recursively check all around the points.

	if (RecursivelyCheckTopToDown(x, y + 1)) {
		return true;
	}
	if (y != 0 && RecursivelyCheckTopToDown(x + 1, y)) {
		return false;
	}
	if (x > 1) {
		if (RecursivelyCheckTopToDown(x - 1, y) || RecursivelyCheckTopToDown(x - 1, y + 1)) {
			return true;
		}
	}
	if (y != 0) {
		if (RecursivelyCheckTopToDown(x, y - 1)) {
			return true;
		}
		if (y != 1 && RecursivelyCheckTopToDown(x + 1, y - 1))
			return true;
	}
	return false;
}

bool Board::RecursivelyCheckLeftToRight(int x, int y) {

	//Already has checked this path.
	if (checkboard[x][y])
		return false;

	checkboard[x][y] = true;

	//At the end of the height
	if (y == height) {
		return false;
	}

	//Check for correct character.
	if (board[x][y] != 'x')
		return false;

	//Has completed left to right row.
	if (x == width - 1) {
		return true;
	}

	//Recursively check all around the points.


	if (RecursivelyCheckLeftToRight(x + 1, y)) {
		return true;
	}
	if (x != 0 && RecursivelyCheckLeftToRight(x, y + 1)) {
		return false;
	}
	if (y > 1) {
		if (RecursivelyCheckLeftToRight(x, y - 1) || RecursivelyCheckLeftToRight(x + 1, y - 1)) {
			return true;
		}
	}
	if (x != 0) {
		if (RecursivelyCheckLeftToRight(x - 1, y)) {
			return true;
		}
		if (x != 1 && RecursivelyCheckLeftToRight(x - 1, y + 1))
			return true;
	}

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

bool Board::IsConnected(int playerNumber)
{
	if (playerNumber == 1)
	{
		return IsConnectedLeftToRight();
	}
	else
	{
		return IsConnectedTopToDown();
	}
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

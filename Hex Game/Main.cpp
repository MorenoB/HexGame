// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h> 
#include "game.h"


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Game* newGame = new Game();
	newGame->Start();
	_getch();
	delete newGame;
	return 0;

}
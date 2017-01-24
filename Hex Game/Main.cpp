// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h> 
#include "game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Game gameObject;
	gameObject.Start();
	_getch();
	return 0;

}
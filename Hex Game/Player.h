#pragma once
#include <string>

class Player
{
public:
	Player();
	~Player();
private:
	std::string name = "John Doe";
	int id = -1;
};
#include <string>
#include "Board.h"
class Game
{
public:
	Game();  // This is the constructor
	void Start();
private:
	int currentPlayer = 1;
	int turnCounter = 1;
	enum PlayerType { HUMAN , AI };
	PlayerType playerType = HUMAN;
	std::string currentInput;
	Board* board;
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
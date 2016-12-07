#pragma once
#include"Board.h"
#include"View.h"

class Game
{
private:
	View* view;
	Board* board;
	int gameMode; // 1 - mean player vs ii // 2 mean ii vs ii
	int startStones; // how many stone will on start of the game in every cell
	int diffucult;  // == deep of move tree
public:
	Game(int startStones_);
	~Game();


};

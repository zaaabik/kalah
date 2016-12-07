#include"game.h"
#define START_VALUE 4
#define COUNT_OF_HOLES 14
Game::Game(int startStones_) {
	diffucult = -1;
	gameMode = -1;
	startStones = startStones_;
	board = new Board(startStones, -1, -1);
	view = new View(board);
	view->gameCycle();
}
Game::~Game() {
	delete board;
	delete view;
}

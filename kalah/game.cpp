#include"game.h"
#define START_VALUE 4
#define COUNT_OF_HOLES 14

/**
 @fn	Game::Game(int startStones_)

 @brief	Constructor.

 @author	Root
 @date	08.12.2016

 @param	startStones_	Number of stones in every cell.
 */

Game::Game(int startStones_) {
	startStones = startStones_;
	board = new Board(startStones, -1);
	view = new View(board);
	view->gameCycle();
}

/**
 @fn	Game::~Game()

 @brief	Destructor.

 @author	Root
 @date	08.12.2016
 */

Game::~Game() {
	delete board;
	delete view;
}

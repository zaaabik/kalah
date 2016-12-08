#include"Board.h"
#include"View.h"
#include<climits>
#include<iostream>

/**
 @fn	void Board::noMove()

 @brief	if one of the player dont have move, other put all stones from is cell into kalah.

 @author	Root
 @date	08.12.2016
 */

void Board::noMove()
{
	bool haveMove = false;
	haveMove = this->haveMove();
	if (!haveMove) {
		if (this->isFirst) {
			int sum = 0;
			for (int i = 7; i < 13; ++i) {
				sum += arrayOfCells[i];
				arrayOfCells[i] = 0;
			}
			arrayOfCells[NUMBER_OF_CELLS  - 1] += sum;
		}
		else {
			int sum = 0;
			for (int i = 0; i < 7; ++i) {
				sum += arrayOfCells[i];
				arrayOfCells[i] = 0;
			}
			arrayOfCells[NUMBER_OF_CELLS / 2 - 1] += sum;
		}
	}
}

/**
 @fn	int Board::getGameMode()

 @brief	Gets game mode.

 @author	Root
 @date	08.12.2016

 @return	The game mode.
 */

int Board::getGameMode() {
	return gameMode;
}

/**
 @fn	void Board::setGameMode(int mode)

 @brief	Sets game mode.

 @author	Root
 @date	08.12.2016

 @param	mode	The game mode.
 */

void Board::setGameMode(int mode) {
	gameMode = mode;
}

/**
 @fn	void Board::setDifficutlt(int difficlit)

 @brief	Sets a difficutlt.

 @author	Root
 @date	08.12.2016

 @param	difficlit	number of moves, which will consider the game for first bot.
 */

void Board::setDifficutlt(int difficlit) {
	diffucult_ = difficlit;
}

/**
 @fn	void Board::setDifficultSecond(int diff)

 @brief	Sets difficult second.

 @author	Root
 @date	08.12.2016

 @param	diff	number of moves, which will consider the game for second bot.
 */

void Board::setDifficultSecond(int diff) {
	difficlultSecond = diff;
}

/**
 @fn	int Board::getDifficlutSecond()

 @brief	Gets difficlut second.

 @author	Root
 @date	08.12.2016

 @return	The difficlut second.
 */

int Board::getDifficlutSecond() {
	return difficlultSecond;
}

/**
 @fn	int Board::getWhoStartMinMax()

 @brief	Gets who start minMax algorithm.

 @author	Root
 @date	08.12.2016

 @return	The calculated who start minimum maximum.
 */

int Board::getWhoStartMinMax() {
	return whoStartMinMax;
}

/**
 @fn	void Board::setWhoStartMinMax(int numberOfPlayer)

 @brief	Sets number of player whick started minimum maximum.

 @author	Root
 @date	08.12.2016

 @param	numberOfPlayer	number of player starting minMax.
 */

void Board::setWhoStartMinMax(int numberOfPlayer) {
	whoStartMinMax = numberOfPlayer;
}

/**
 @fn	bool Board::haveMove()

 @brief	Determines if we can have move.

 @author	Root
 @date	08.12.2016

 @return	True if have move, false if not.
 */

bool Board::haveMove() {
	bool haveMove = false;
	if (this->isFirstMove()) {

		for (int i = 0; i < CELLS; ++i) {
			if (canMove(i)) {
				haveMove = true;
			}
		}
	}
	else {

		for (int i = 7; i < 13; ++i) {
			if (canMove(i)) {
				haveMove = true;
			}
		}
	}
	return haveMove;
}

/**
 @fn	Board::Board(int start_value, int gameMode_,int difficult)

 @brief	Constructor.

 @author	Root
 @date	08.12.2016

 @param	start_value	Number of stones in every cell.
 @param	gameMode_  	The game mode
					1) player vs bot
					2)bot vs bot
 @param	difficult  	The difficult (number of moves, which will consider the game for first bot).
 */

Board::Board(int start_value, int gameMode_) {
	arrayOfCells.resize(NUMBER_OF_CELLS);					//resize vector to size of gamefield
	prevArrayOfCells.resize(NUMBER_OF_CELLS);				//resize vector of previous move gamefield
	for (int i = 0; i < NUMBER_OF_CELLS; ++i) {
		if (i != NUMBER_OF_CELLS / 2 - 1 
					 && 
			i != NUMBER_OF_CELLS - 1)
			arrayOfCells[i] = start_value;					//overy cell get the start number of stones
		else
			arrayOfCells[i] = 0;
	}
	isFirst = true;
	endGame = 0;
	gameMode = gameMode_;
	stones = start_value * (NUMBER_OF_CELLS - 2);
}

/**
 @fn	Board::~Board()

 @brief	Destructor.

 @author	Root
 @date	08.12.2016
 */

Board::~Board() {

}

/**
 @fn	Board::Board(Board & obj)

 @brief	Copy constructor.

 @author	Root
 @date	08.12.2016

 @param [in,out]	obj	The object.
 */

Board::Board(Board & obj) {
	arrayOfCells = obj.arrayOfCells;
	isFirst = obj.isFirst;
	endGame = 0;
	gameMode = obj.gameMode;
	arrayOfCells = obj.arrayOfCells;
	stones = obj.stones;
	diffucult_ = obj.diffucult_;
	difficlultSecond = obj.difficlultSecond;
	whoStartMinMax = obj.whoStartMinMax;
}

/**
 @fn	bool Board::canMove(int cell_number)

 @brief	Determine if we can move of cell_number.

 @author	Root
 @date	08.12.2016

 @param	cell_number	The cell number.

 @return	True if we can move, false if not.
 */

bool Board::canMove(int cell_number) {
	if (arrayOfCells[cell_number] != 0)
		return true;
	return false;
}

/**
 @fn	void Board::move(int cell_number)

 @brief	make a move from cell.

 @author	Root
 @date	08.12.2016

 @param	cell_number	The cell number from which the move will be made.
 */

void Board::move(int cell_number) {

	if (canMove(cell_number)) {
		prevArrayOfCells = arrayOfCells;
		prevMove = isFirst;
		int tmp = arrayOfCells[cell_number];
		arrayOfCells[cell_number] = 0;
		if (isFirst && arrayOfCells[(cell_number + tmp) % NUMBER_OF_CELLS] == 0 && (cell_number + tmp) % NUMBER_OF_CELLS >= 0 && (cell_number + tmp) % NUMBER_OF_CELLS <= 5) {

			arrayOfCells[CELLS] += arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2];  // when you hit into the empty cell you take stones from opposite cell
			arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2] = 0;
		}
		else if (!isFirst && arrayOfCells[(cell_number + tmp) % NUMBER_OF_CELLS] == 0 && (cell_number + tmp) % NUMBER_OF_CELLS >= 7 && (cell_number + tmp) % NUMBER_OF_CELLS <= 12) {
			arrayOfCells[CELLS * 2 + 1] += arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2];
			arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2] = 0;
		}
		for (int i = cell_number + 1; i < cell_number + 1 + tmp; ++i) {
			if (isFirst && i % NUMBER_OF_CELLS == CELLS * 2 + 1) {
				tmp++;
				i++;
			}
			else if (!isFirst && i % NUMBER_OF_CELLS == CELLS) {
				tmp++;
				i++;
			}
			arrayOfCells[i % NUMBER_OF_CELLS]++;
		}

		if (isFirst && (cell_number + tmp) % NUMBER_OF_CELLS == CELLS) {

		}
		else if (!isFirst && (cell_number + tmp) % NUMBER_OF_CELLS == 13) {

		}
		else {
			isFirst = !isFirst;
		}
	}



}

/**
 @fn	int Board::isWin()

 @brief	return not zero value if game is finished.

 @author	Root
 @date	08.12.2016

 @return  1 = first player is win
          2 = second player is win
	      3 = tie.
 */

int Board::isWin() {
	int a = 0;
	bool haveMove = this->haveMove();	
	this->noMove();
	if(!this->haveMove()  && arrayOfCells[NUMBER_OF_CELLS / 2 - 1] == arrayOfCells[NUMBER_OF_CELLS - 1])
	{
		return 3; // tie
	}
	else if (arrayOfCells[NUMBER_OF_CELLS / 2 - 1] > (stones / 2)
		||
		(!this->haveMove() && arrayOfCells[NUMBER_OF_CELLS / 2 - 1] > arrayOfCells[NUMBER_OF_CELLS - 1])
		) {														//if number of stones in player`s kalah more then (all stones in the game / 2) he win!) {				   //or if one player dont have any moves
		a = arrayOfCells[NUMBER_OF_CELLS / 2 - 1];
		return 1; // first player win
	}
	else if (arrayOfCells[NUMBER_OF_CELLS - 1] > (stones / 2)
							||
		(!this->haveMove() && arrayOfCells[NUMBER_OF_CELLS - 1] > arrayOfCells[NUMBER_OF_CELLS / 2 - 1])
		) {
		return 2; // second player win
	}
	else {
		return 0; // game isnt finished 
	}
}

/**
 @fn	int Board::getCell(int cell_number)

 @brief	Gets a stones from cell.

 @author	Root
 @date	08.12.2016

 @param	cell_number	The cell number.

 @return	Count of stones in the cell.
 */

int Board::getCell(int cell_number) {
	return arrayOfCells[cell_number];
}

/**
 @fn	bool Board::isFirstMove()

 @brief	Return which move now.

 @author	Root
 @date	08.12.2016

 @return	True if first move, false if not.
 */

bool Board::isFirstMove() {
	return isFirst;
}

result Board::abMiniMax(int deep, Board board, int alpha, int beta) {
	result tmp;
	tmp.move_number = -1;																														   //alpha - best for max
	if(board.getGameMode() == 1 && (board.isWin() || board.getDifficult() <= deep || !board.haveMove()))
	{
		board.noMove();
		result a;
		a.value = board.kalahsDiffirent();
		return a;
	}
	if (				board.getGameMode() == 2 
								&& 
								(
			(!board.haveMove()  || board.isWin())
								||
		(board.getWhoStartMinMax() == 1 && board.getDifficult() <= deep)
								||
		(board.getWhoStartMinMax() == 0 && board.getDifficlutSecond() <= deep)
			
								)
		) {								    //beta - best for min
		board.noMove();
		result a;
		a.value = board.kalahsDiffirent();			
		return a;
	}

	bool wasMove = false;
	if (board.isFirstMove()) {

		tmp.value = INT_MAX;
		tmp.move_number = -1;
		for (int i = 0; i < CELLS; ++i) {

			if (board.canMove(i)) {

				board.move(i);
				wasMove = true;
				int tmp_res = abMiniMax(deep + 1, board, alpha, beta).value;
				if (tmp_res < tmp.value) {
					tmp.value = tmp_res;
					tmp.move_number = i;
				}
				board.undoMove(i);											//beta best options for the min
				if (tmp.value < alpha) {									//alpha pruning
					if (tmp.value == INT_MAX) {
						board.noMove();													//if player dont have any move - return current kalah different
						tmp.value = board.kalahsDiffirent();
					}
					return tmp;
				}
				if (beta > tmp.value) {
					beta = tmp.value;
				}
			}
		}
		if (tmp.value == INT_MAX) {
			board.noMove();
			tmp.value = board.kalahsDiffirent();
		}
		return tmp;
	}
	else {
		tmp.value = INT_MIN;
		tmp.move_number = -CELLS;
		for (int i = 7; i < 13; ++i) {
			if (board.canMove(i)) {
				board.move(i);
				int tmp_res = abMiniMax(deep + 1, board, alpha, beta).value;
				if (tmp_res > tmp.value) {
					tmp.value = tmp_res;
					tmp.move_number = i;
				}
				board.undoMove(i);									//best best options for the min
				if (tmp_res > beta) {								//bets pruning
					if (tmp.value == INT_MIN) {	
						board.noMove();								//if player dont have any move - return current kalah different
						tmp.value = board.kalahsDiffirent();
					}
					return tmp;
				}
				else if(alpha < tmp_res){
					alpha = tmp_res;
				}
			}
		}
		if (tmp.value == INT_MIN) {
			board.noMove();
			tmp.value = board.kalahsDiffirent();
		}
		return tmp;
	}
}

/**
 @fn	void Board::iiMove()

 @brief	Make ii move.

 @author	Root
 @date	08.12.2016
 */

void Board::iiMove() {
	Board tmp = *this;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	tmp.setWhoStartMinMax(this->isFirst);
	result tmp2 = abMiniMax(0, tmp, alpha, beta);
	this->move(tmp2.move_number);
}

/**
 @fn	void Board::undoMove(int cell)

 @brief	Undo move from cell.

 @author	Root
 @date	08.12.2016

 @param	cell	The cell in which last move was made.
 */

void Board::undoMove(int cell) {
	arrayOfCells = prevArrayOfCells;
	isFirst = prevMove;
}

int Board::kalahsDiffirent() {
	return arrayOfCells[NUMBER_OF_CELLS - 1] - arrayOfCells[NUMBER_OF_CELLS / 2 - 1];
}

/**
 @fn	void Board::changeMove()

 @brief	Change player making a move.

 @author	Root
 @date	08.12.2016
 */

void Board::changeMove() {
	isFirst = !isFirst;
}

/**
 @fn	int Board::getDifficult()

 @brief	Gets the difficult.

 @author	Root
 @date	08.12.2016

 @return	The difficult.
 */

int Board::getDifficult() {
	return this->diffucult_;
}

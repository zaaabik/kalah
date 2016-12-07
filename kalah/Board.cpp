#include"Board.h"
#include"View.h"
#include<climits>
#include<iostream>
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

int Board::getGameMode() {
	return gameMode;
}

void Board::setGameMode(int mode) {
	gameMode = mode;
}

void Board::setDifficutlt(int difficlit) {
	diffucult_ = difficlit;
}

void Board::setDifficultSecond(int diff) {
	difficlultSecond = diff;
}

int Board::getDifficlutSecond() {
	return difficlultSecond;
}

int Board::getWhoStartMinMax() {
	return whoStartMinMax;
}

void Board::setWhoStartMinMax(int numberOfPlayer) {
	whoStartMinMax = numberOfPlayer;
}

typedef struct result
{
	int value = 0;
	int move_number = 0;
}result;
bool Board::haveMove() {
	bool haveMove = false;
	if (this->isFirstMove()) {

		for (int i = 0; i < 6; ++i) {
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

Board::Board(int start_value, int gameMode_,int difficult) {
	diffucult_ = difficult;
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
	/*arrayOfCells[0] = 0;
	arrayOfCells[1] = 0;
	arrayOfCells[2] = 0;
	arrayOfCells[3] = 0;
	arrayOfCells[4] = 0;
	arrayOfCells[5] = 0;
	arrayOfCells[6] = 0;
	arrayOfCells[7] = 0;
	arrayOfCells[8] = 0;
	arrayOfCells[9] = 0;
	arrayOfCells[10] = 0;
	arrayOfCells[11] = 0;
	arrayOfCells[12] = 0;
	arrayOfCells[13] = 0;*/
	isFirst = true;
	endGame = 0;
	gameMode = gameMode_;
	stones = start_value * (NUMBER_OF_CELLS - 2);
}

Board::~Board() {

}

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

bool Board::canMove(int cell_number) {
	if (arrayOfCells[cell_number] != 0)
		return true;
	return false;
}

void Board::move(int cell_number) {

	if (canMove(cell_number)) {
		prevArrayOfCells = arrayOfCells;
		prevMove = isFirst;
		int tmp = arrayOfCells[cell_number];
		arrayOfCells[cell_number] = 0;
		if (isFirst && arrayOfCells[(cell_number + tmp) % NUMBER_OF_CELLS] == 0 && (cell_number + tmp) % NUMBER_OF_CELLS >= 0 && (cell_number + tmp) % NUMBER_OF_CELLS <= 5) {

			arrayOfCells[6] += arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2];  // when you hit into the empty cell you take stones from opposite cell
			arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2] = 0;
		}
		else if (!isFirst && arrayOfCells[(cell_number + tmp) % NUMBER_OF_CELLS] == 0 && (cell_number + tmp) % NUMBER_OF_CELLS >= 7 && (cell_number + tmp) % NUMBER_OF_CELLS <= 12) {
			arrayOfCells[13] += arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2];
			arrayOfCells[NUMBER_OF_CELLS - (cell_number + tmp) % NUMBER_OF_CELLS - 2] = 0;
		}
		for (int i = cell_number + 1; i < cell_number + 1 + tmp; ++i) {
			if (isFirst && i % NUMBER_OF_CELLS == 13) {
				tmp++;
				i++;
			}
			else if (!isFirst && i % NUMBER_OF_CELLS == 6) {
				tmp++;
				i++;
			}
			arrayOfCells[i % NUMBER_OF_CELLS]++;
		}

		if (isFirst && (cell_number + tmp) % NUMBER_OF_CELLS == 6) {

		}
		else if (!isFirst && (cell_number + tmp) % NUMBER_OF_CELLS == 13) {

		}
		else {
			isFirst = !isFirst;
		}
	}



}

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

int Board::getCell(int cell_number) {
	return arrayOfCells[cell_number];
}

bool Board::isFirstMove() {
	return isFirst;
}

result abMiniMax(int deep, Board board, int alpha, int beta) {
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
		for (int i = 0; i < 6; ++i) {

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
		tmp.move_number = -6;
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

void Board::iiMove() {
	Board tmp = *this;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	tmp.setWhoStartMinMax(this->isFirst);
	result tmp2 = abMiniMax(0, tmp, alpha, beta);
	this->move(tmp2.move_number);
}

void Board::undoMove(int cell) {
	arrayOfCells = prevArrayOfCells;
	isFirst = prevMove;
}

int Board::kalahsDiffirent() {
	return arrayOfCells[NUMBER_OF_CELLS - 1] - arrayOfCells[NUMBER_OF_CELLS / 2 - 1];
}

void Board::changeMove() {
	isFirst = !isFirst;
}

int Board::getDifficult() {
	return this->diffucult_;
}

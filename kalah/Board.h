#pragma once
#define NUMBER_OF_CELLS 14
#include<vector>
class Board
{
private:

	bool isFirst;
	int endGame;						  // 0 = game isnt finished  1 = first win 2 = second win
	std::vector<int> arrayOfCells;        //cells
	int gameMode;						  // game mode
	int stones;							  // number of stones in this game
	std::vector<int> prevArrayOfCells;	  // previous state of array 
	bool prevMove;						  // whose move was previous
	int diffucult_;
	int difficlultSecond;
	int whoStartMinMax;
public:
	Board(int start_value, int gameMode_,int difficult);
	Board(Board& obj);
	~Board();
	bool haveMove();
	bool canMove(int cell_number);
	void move(int cell_number);
	int isWin();
	int getCell(int cell_number);
	bool isFirstMove();
	void iiMove();						//start dfs and choose the best var of move
	void undoMove(int cell);			//undo prev move
	int kalahsDiffirent();
	void changeMove();
	int getDifficult();
	void noMove();
	int getGameMode();
	void setGameMode(int mode);
	void setDifficutlt(int difficult);
	void setDifficultSecond(int diff);
	int getDifficlutSecond();
	int getWhoStartMinMax();
	void setWhoStartMinMax(int numberOfPlayer);

};


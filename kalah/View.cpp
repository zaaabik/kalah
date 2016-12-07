#include"View.h"
#include<stdio.h>
#include<iostream>
#include<time.h>
#include<string>
#include<fstream>
#include "button.h"
#define CELL_SIZE 85
#define PADDING_LEFT_4_CELLS 95
#define FIRST_PLAYER 200
#define SECOND_PLAYER 50
typedef struct cellIsClicked
{
	int cell;
	bool isClicked;
}cellIsClicked;
void chooseDificultWindow(sf::RenderWindow& window, Board& gameBoard, int PlayerNumber)
{
	Button easy("Easy", window.getSize().x / 2, window.getSize().y / 2 - 100);
	Button medium("Medium", window.getSize().x / 2, window.getSize().y / 2 - 50);
	Button hard("Hard", window.getSize().x / 2, window.getSize().y / 2);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		easy.showButton(window);
		medium.showButton(window);
		hard.showButton(window);
		if (PlayerNumber == 1) {
			if (easy.isPressed(window, event)) {
				gameBoard.setDifficutlt(1);
				break;
			}
			else if (medium.isPressed(window, event)) {
				gameBoard.setDifficutlt(6);
				break;
			}
			else if (hard.isPressed(window, event)) {
				gameBoard.setDifficutlt(10);
				break;
			}
		}
		if (PlayerNumber == 2)
		{
			if (easy.isPressed(window, event)) {
				gameBoard.setDifficultSecond(1);
				break;
			}
			if (medium.isPressed(window, event)) {
				gameBoard.setDifficultSecond(6);
				break;
			}
			if (hard.isPressed(window, event)) {
				gameBoard.setDifficultSecond(10);
				break;
			}
		}
			window.display();
			window.clear(sf::Color(80, 85, 63));
		
	}
}
void View::showText(sf::RenderWindow& window, sf::String text_, int x, int y, int type)
{
	if(type == 1) //mainMenu
	{
		sf::Text text;
		text.setString(text_);
		text.setFont(mainMenuFont);
		sf::IntRect tmpRect = (sf::IntRect)text.getLocalBounds();
		text.setPosition(x + (tmpRect.left - tmpRect.width / 2  ), y + (tmpRect.top - tmpRect.height / 2 ));
		window.draw(text);
	}
	else if (type == 2) //gameLoop
	{
		sf::Text text;
		text.setString(text_);
		text.setFont(font);
		sf::IntRect tmpRect = (sf::IntRect)text.getLocalBounds();
		text.setPosition(x + (tmpRect.left - tmpRect.width / 2), y + (tmpRect.top - tmpRect.height / 2));
		text.setPosition(x, y);
		window.draw(text);
	}
}
cellIsClicked choosCell(sf::RenderWindow& window, sf::Event event1) {
	sf::Time a;
	sf::Mouse mouse;
	cellIsClicked res;
	window.setKeyRepeatEnabled(false);
	sf::Event event;
	window.pollEvent(event);
	res.cell = -1;
	res.isClicked = false;
	if (mouse.getPosition(window).y >= 200 && mouse.getPosition(window).y <= 280) {
		res.cell = (mouse.getPosition(window).x - PADDING_LEFT_4_CELLS) / CELL_SIZE;
		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
			res.isClicked = true;
		}
	
		return res;
	}
	else if (mouse.getPosition(window).y >= 50 && mouse.getPosition(window).y <= 50 + 80) {
		res.cell = (window.getSize().x - mouse.getPosition(window).x - PADDING_LEFT_4_CELLS) / CELL_SIZE + 7;
		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
			res.isClicked = true;
		}
		return res;
	}
	else {
		return res;
	}
}

void View::showALlCells(sf::RenderWindow& window) {
	sf::Text textFont("hello", font, 50);
	textFont.setColor(sf::Color(188, 185, 104));
	sf::String str;
	char buf[25];
	
	for(int i = 0; i < 6;++i){
		itoa(board->getCell(i), buf, 10);
		str = buf;
		textFont.setString(str);
		textFont.setPosition(PADDING_LEFT_4_CELLS + CELL_SIZE * i + CELL_SIZE / 4, FIRST_PLAYER);
		window.draw(textFont);
	}
	for (int i = 7; i < 13; ++i) {
		itoa(board->getCell(i), buf, 10);
		str = buf;
		textFont.setString(str);
		textFont.setPosition(PADDING_LEFT_4_CELLS + CELL_SIZE * (-(i % 6 - 6) % 6) + CELL_SIZE / 4, SECOND_PLAYER);
		window.draw(textFont);
	}
}

void View::showKalahs(sf::RenderWindow& window) {
	sf::Text textFont("hello", font, 80);
	textFont.setColor(sf::Color(188, 185, 104));
	sf::String str;
	char buf[25];
	itoa(board->getCell(6), buf, 10);
	str = buf;
	textFont.setString(str);
	textFont.setPosition(635, 90);
	window.draw(textFont);
	itoa(board->getCell(13), buf, 10);
	str = buf;
	textFont.setString(str);
	textFont.setPosition(20, 90);
	window.draw(textFont);
}

void View::mainMenu(sf::RenderWindow& window) {
	
	sf::Text mainMenuText;
	sf::String a;
	sf::Texture backTexture;
	std::ofstream log("log.txt", std::ios::out);
	if(!backTexture.loadFromFile("Media\\back.jpg"))
	{
		log << "Missing back.jpg";
	}
	log.close();
	sf::Sprite backSprite;
	backSprite.setTexture(backTexture, true);
	
	Button SinglePlayer("SINGLE PLAYER", window.getSize().x / 2, window.getSize().y / 2 - 90);
	Button ComputerWar("COMPUTER WARS!!!", window.getSize().x / 2, window.getSize().y / 2 + 30 - 70);
	
	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		showText(window, "KALAH", window.getSize().x / 2, 50, 1);
		SinglePlayer.showButton(window);
		if(SinglePlayer.isPressed(window, event))
		{
			board->setGameMode(1);
			break;
		}
		if(ComputerWar.isPressed(window, event))
		{
			board->setGameMode(2);
			break;
		}
		ComputerWar.showButton(window);
		window.display();
		window.clear(sf::Color(80,85,63));
	}

	std::cout << "exit" << std::endl;
}



int View::chooseMove(sf::RenderWindow& window,sf::Event& ev) {
	cellIsClicked res;
	res.isClicked = false;
	res.cell = -1;
	res = choosCell(window, ev);
	
	
	if ((res.cell >= 0 && res.cell <= 5) && board->canMove(res.cell) && res.isClicked)
	{
		return res.cell;
	}
	return -1;

}
View::View(Board* board_) {
	board = board_;
	std::ofstream log("log.txt", std::ios::out);
	if(!cellTexture.loadFromFile("Media\\cell.png")){ 
		log << "cell.png doestn exist!";
	}
	cell.setTexture(cellTexture);
	if (!mainMenuFont.loadFromFile("Media\\mainMenuFont.otf")) {
		log << "Main menu`s font doesnt exist!";
	}
	if (!KalahTexture.loadFromFile("Media\\kalah.png")) {
		log << "kalah.png doestn exist!";
	}
	kalah.setTexture(KalahTexture);

	if (!stoneTexture.loadFromFile("Media\\stone.png")) {
		log << "Media\\stonge.png doesnt exist!";
	}
	stone.setTexture(stoneTexture);
	if (!font.loadFromFile("Media\\Akrobat.otf")) {
		log << "font doesnt exist!";
	}
}
View::~View() {
}
void View::showBoard(sf::RenderWindow& window) {
	window.clear(sf::Color(80,85,63));
	kalah.setPosition(0, 90);        // show kalah
	window.draw(kalah);
	kalah.setPosition(615, 90);
	window.draw(kalah);
		
	for (int i = 0; i < 6; ++i){													//show 2 player cells
		cell.setPosition(i * CELL_SIZE + PADDING_LEFT_4_CELLS, SECOND_PLAYER);
		window.draw(cell);
	}
	for (int i = 0; i < 6; ++i) {													//show 1 player cells
		cell.setPosition(i * CELL_SIZE + PADDING_LEFT_4_CELLS, FIRST_PLAYER);
		window.draw(cell);
	}
	showALlCells(window);
	showKalahs(window);
	int win = board->isWin();
	sf::Text tx;
	tx.setFont(font);
	tx.setPosition(250, 125);
	sf::String str;
	
	if(win){
		if(win == 1){
			str = "FIRST PLAYER WIN!";
		}
		else if(win == 2) {
			str = "SECOND PLAYER WIN!";
		}
		else if(win == 3 )
		{
			str = "TIE :C";
		}
		tx.setString(str);
		window.draw(tx);
	}
	else if(board->isFirstMove() && board->getGameMode() != 2)
	{
		str = "your turn!";
		tx.setString(str);
		window.draw(tx);
	}
	window.display();
	window.clear(sf::Color(80,85,63));

}
void View::showBoard() {
	for (int i = NUMBER_OF_CELLS - 2; i >= NUMBER_OF_CELLS / 2; --i) {
		printf(" %d ", board->getCell(i));
	}
	printf("\n");
	printf("%d", board->getCell(NUMBER_OF_CELLS - 1));
	for (int i = 0; i <= NUMBER_OF_CELLS / 2; i++) {
		printf("  ");
	}
	printf("%d", board->getCell(NUMBER_OF_CELLS / 2 - 1));
	printf("\n");
	for (int i = 0; i <= NUMBER_OF_CELLS / 2 - 2; ++i) {
		printf(" %d ", board->getCell(i));
	}
	printf("\n\n");
}
void View::gameCycle() {
	//  1 - game mode player vs ii
	//  2 - game mode ii vs ii
	sf::RenderWindow window(sf::VideoMode(700, 393), "Kalah game");
	mainMenu(window);
	chooseDificultWindow(window, *board,1);
	chooseDificultWindow(window, *board,2);
	if (board->getGameMode() == 1) {
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						window.close();
				}
				showBoard(window);
				if (!board->isWin()) {
					if (board->isFirstMove()) {
						int move = -1;
						move = chooseMove(window, event);
						if (move != -1) {
							std::cout << move;
							board->move(move);
						}
					}
					else {
						board->iiMove();
						showBoard(window);
					}
				}
		}
	}
	else {
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			showBoard(window);
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (!board->isWin()) {
				board->setWhoStartMinMax(board->isFirstMove());
				board->iiMove();
				sf::sleep(sf::milliseconds(100));
			}
		}
	}
}
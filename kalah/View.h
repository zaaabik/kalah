#pragma once
#include"Board.h"
#include<SFML\Graphics.hpp>
class View
{
private:
	Board* board;
	sf::Sprite kalah;
	sf::Sprite stone;
	sf::Sprite cell;
	sf::Texture KalahTexture;
	sf::Texture cellTexture;
	sf::Texture stoneTexture;
	sf::Font font;
	sf::Font mainMenuFont;
public:
	View(Board* board_);
	~View();
	void showBoard(sf::RenderWindow& window);
	void showBoard();
	void gameCycle();
	int chooseMove(sf::RenderWindow& window, sf::Event& even);
	void showALlCells(sf::RenderWindow& window);
	void showKalahs(sf::RenderWindow& window);
	void mainMenu(sf::RenderWindow& window);
	void showText(sf::RenderWindow& window, sf::String text, int x, int y, int type);
};

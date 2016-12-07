#pragma once
#include<SFML\Graphics.hpp>
class Button
{
public:
	Button(sf::String buttonName, int x, int y);
	~Button();
	void showButton(sf::RenderWindow& window);
	bool isPressed(sf::RenderWindow& window, sf::Event& event);
private:
	sf::Font buttonFont;
	sf::Text buttonText;
	int x;
	int y;
};

#include "button.h"
#include<iostream>
Button::Button(sf::String buttonName, int x_, int y_) {
	if(buttonFont.loadFromFile("Media\\mainMenuFont.otf"))
	{
	}
	x = x_;
	y = y_;
	buttonText.setFont(buttonFont);
	buttonText.setString(buttonName);
	sf::IntRect tmpRect = (sf::IntRect)buttonText.getLocalBounds();
	x = x + (tmpRect.left - tmpRect.width / 2);
	y = y + (tmpRect.top - tmpRect.height / 2);
	buttonText.setPosition(x,y);
}

Button::~Button() {
}
bool isInInterval(int x, int y, int point) {
	if(x <= point && y >= point)
	{
		return true;
	}
	return false;
	
}

void Button::showButton(sf::RenderWindow& window) {
	window.draw(buttonText);
}

bool Button::isPressed(sf::RenderWindow& window, sf::Event& event) {
	if (isInInterval(y, y + buttonText.getCharacterSize(), sf::Mouse::getPosition(window).y)
												&&
		(event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) /*|| (sf::Mouse::isButtonPressed(sf::Mouse::Left))*/
												&&
		isInInterval(x, x + buttonText.getLocalBounds().width, sf::Mouse::getPosition(window).x)
		)
	{
		return true;
	}
	return false;
	
}


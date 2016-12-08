#include "button.h"
#include<iostream>

/**
 @fn	Button::Button(sf::String buttonName, int x_, int y_)

 @brief	Constructor.

 @author	Root
 @date	08.12.2016

 @param	buttonName	Name of the button.
 @param	x_		  	The x coordinate.
 @param	y_		  	The y coordinate.
 */

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

/**
 @fn	Button::~Button()

 @brief	Destructor.

 @author	Root
 @date	08.12.2016
 */

Button::~Button() {
}

bool isInInterval(int x, int y, int point) {
	if(x <= point && y >= point)
	{
		return true;
	}
	return false;
	
}

/**
 @fn	void Button::showButton(sf::RenderWindow& window)

 @brief	Shows the button.

 @author	Root
 @date	08.12.2016

 @param [in,out]	window	the window in which button will be displayed.
 */

void Button::showButton(sf::RenderWindow& window) {
	window.draw(buttonText);
}

/**
 @fn	bool Button::isPressed(sf::RenderWindow& window, sf::Event& event)

 @brief	Query if 'window' is pressed.

 @author	Root
 @date	08.12.2016

 @param [in,out]	window	current window.
 @param [in,out]	event 	current window`s event.

 @return	True if pressed, false if not.
 */

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


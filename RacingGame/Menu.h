#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define SCREEN_X 1920
#define SCREEN_Y 1080

namespace Menu
{
	//opens the window displays the game's main menu screen
	//returns 1 for 1-player, 2 for 2-player and 0 for exit
	int runMenu();

	//checks to see if the mouse is within the bounds of the shape
	bool checkMouseBounds(sf::Event &event, sf::RectangleShape shape);

	bool checkMouseBounds(sf::Mouse &mouse, sf::RectangleShape &shape, sf::RenderWindow *gameWindow);

	class Button : public sf::Drawable
	{
	public:
		Button(sf::Text text, sf::Vector2f size = sf::Vector2f(20.0f, 10.0f));
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void setPosition(sf::Vector2f pos);

		//returns the rectangle shape of the button
		sf::RectangleShape & getShape();
		//changes the color of the rectangle to a darker shade
		void darken();
		//resets the color to the original 
		void lighten();
		//sets the bool value regarding whether the mouse is over the button
		void setBool(bool newValue);
		//returns the bool value regarding the mouse being over the button
		bool getBool();

		//returns the bool if the button is to be shown or not
		bool getIfShown();
		//sets the visibility of the button
		void setShown(bool newValue);

	private:
		sf::RectangleShape shape;
		sf::Text text;
		sf::Font font;
		bool mouseOnButton;
		bool shown;
	};


}
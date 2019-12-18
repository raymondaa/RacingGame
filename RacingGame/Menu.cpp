#include "Menu.h"

Menu::Button::Button(sf::Text text, sf::Vector2f size)
{
	font.loadFromFile("INVASION2000.TTF");
	this->text = text;
	this->text.setFont(font);

	shape.setSize(size);

	this->setPosition(sf::Vector2f(30.0f, 30.0f));

	//shape.setFillColor(sf::Color::White);
	this->text.setFillColor(sf::Color::Color(212, 49, 51, 255));
	this->text.setCharacterSize(75);
	//this->text.setOutlineColor(sf::Color::Black);
	//this->text.setOutlineThickness(.33);
	shown = true;
}

void Menu::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}

void Menu::Button::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
	float height, width;
	height = (shape.getPosition().y) + (shape.getLocalBounds().height / 2) - text.getLocalBounds().height *.65;
	width = (shape.getPosition().x) + shape.getLocalBounds().width / 2 - (text.getLocalBounds().width) *.5;
	text.setPosition(sf::Vector2f(width, height));
}

sf::RectangleShape & Menu::Button::getShape()
{
	return shape;
}


void Menu::Button::darken()
{
	shape.setFillColor(sf::Color::White);
}

void Menu::Button::lighten()
{
	shape.setFillColor(sf::Color::Black);
}

void Menu::Button::setBool(bool newValue)
{
	mouseOnButton = newValue;
}

bool Menu::Button::getBool()
{
	return mouseOnButton;
}

bool Menu::Button::getIfShown()
{
	return shown;
}

void Menu::Button::setShown(bool newValue)
{
	shown = newValue;
}

int Menu::runMenu()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Andy 500");

	// loads and sets background sprite
	sf::Texture backg;
	sf::Sprite background;
	backg.loadFromFile("MenuBackGround.png");
	background.setTexture(backg);

	sf::Text texts[25];

	sf::Mouse mouse;
	sf::Event event, event2;
	sf::Text text;

	text.setString("1-Player");
	Menu::Button onePlayButton(text, sf::Vector2f(500.0f, 100.0f));
	text.setString("2-Player");
	Menu::Button twoPlayButton(text, sf::Vector2f(500.0f, 100.0f));
	text.setString("Instructions");
	Menu::Button instructButton(text, sf::Vector2f(550.0f, 100.0f));
	text.setString("Exit");
	Menu::Button exitButton(text, sf::Vector2f(500.0f, 100.0f));
	sf::Vector2f temp(0, 0);
	temp.x = window.getSize().x / 25;
	temp.y = window.getSize().y / 4 + 50;
	onePlayButton.setPosition(temp);
	temp.y += window.getSize().y / 6;
	twoPlayButton.setPosition(temp);
	temp.y += window.getSize().y / 6;
	instructButton.setPosition(temp);
	temp.y += window.getSize().y / 6;
	exitButton.setPosition(temp);

	sf::RectangleShape shape = onePlayButton.getShape();
	onePlayButton.setBool(false);

	bool gameMenu = false;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		///Figure out why this function is running slowly
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) // is there a mouse click AND is the mouse over the button?
		{
			if (checkMouseBounds(mouse, onePlayButton.getShape(), &window)) ///BUTTON HAS TO BE PRESSED AND HELD
			{
				window.close();
				return 1; // option 1
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseBounds(mouse, twoPlayButton.getShape(), &window))
			{
				window.close();
				return 2; // option 2
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseBounds(mouse, instructButton.getShape(), &window))
			{
				sf::RenderWindow instructWindow(sf::VideoMode(.5 * SCREEN_X, .5 * SCREEN_Y), "Instructions"); //brings up new instruction window
				sf::Texture image;
				sf::Sprite instructions;
				image.loadFromFile("Instructions.png");
				instructions.setTexture(image);

				while (instructWindow.isOpen())
				{
					while (instructWindow.pollEvent(event2))
					{
						if (event2.type == sf::Event::Closed)
							instructWindow.close();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						instructWindow.close();

					instructWindow.draw(instructions);
					instructWindow.display();
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseBounds(mouse, exitButton.getShape(), &window))
				window.close();
			return 0;
		}


		if (Menu::checkMouseBounds(event, shape))
			onePlayButton.setBool(true);
		else
			onePlayButton.setBool(false);

		if (checkMouseBounds(event, twoPlayButton.getShape()))
			twoPlayButton.setBool(true);
		else
			twoPlayButton.setBool(false);

		if (checkMouseBounds(event, instructButton.getShape()))
			instructButton.setBool(true);
		else
			instructButton.setBool(false);

		if (checkMouseBounds(event, exitButton.getShape()))
			exitButton.setBool(true);
		else
			exitButton.setBool(false);



		if (onePlayButton.getBool()) //changes the color of the button in relation to the mouse hovering over it
			onePlayButton.darken();
		else
			onePlayButton.lighten();

		if (twoPlayButton.getBool())
			twoPlayButton.darken();
		else
			twoPlayButton.lighten();

		if (instructButton.getBool())
			instructButton.darken();
		else
			instructButton.lighten();

		if (exitButton.getBool())
			exitButton.darken();
		else
			exitButton.lighten();

		window.clear();
		window.draw(background);

		if (onePlayButton.getIfShown()) // enables the buttons to be hidden if need be
			window.draw(onePlayButton);
		if (twoPlayButton.getIfShown())
			window.draw(twoPlayButton);
		if (instructButton.getIfShown())
			window.draw(instructButton);
		if (exitButton.getIfShown())
			window.draw(exitButton);

		window.display();

	}
}

bool Menu::checkMouseBounds(sf::Event & event, sf::RectangleShape shape)
{
	int mXPos = event.mouseMove.x;
	int mYPos = event.mouseMove.y;


	//checks if the mouse's x AND y position is within the bounds of the box
	if ((mXPos >= shape.getPosition().x && mXPos < (shape.getPosition().x + shape.getSize().x)) && mYPos >= shape.getPosition().y && mYPos < (shape.getPosition().y + shape.getSize().y))
		return true;
	else
		return false;
}

bool Menu::checkMouseBounds(sf::Mouse & mouse, sf::RectangleShape & shape, sf::RenderWindow *gameWindow)
{
	int mXPos = mouse.getPosition(*gameWindow).x;
	int mYPos = mouse.getPosition(*gameWindow).y;

	//std::cout << "XPos Mouse: " << mXPos << std::endl;
	//std::cout << "YPos Mouse: " << mYPos << std::endl;
	//std::cout << "XPos Button: " << shape.getGlobalBounds().left << std::endl;
	//std::cout << "YPos Button: " << shape.getGlobalBounds().top << std::endl;

	//checks if the mouse's x AND y position is within the bounds of the box
	if ((mXPos >= shape.getPosition().x && mXPos < (shape.getPosition().x + shape.getSize().x)) && mYPos >= shape.getPosition().y && mYPos < (shape.getPosition().y + shape.getSize().y))
		return true;
	else
		return false;

}
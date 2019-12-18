#include <SFML/Graphics.hpp>
#include "Car.h"
#include <cstring>
#include <string>

#define LINEAR_SPEED 1
#define ROTATE_SPEED .53
#define PENALTY .25

int main(void) // car movement
{

	double linSpeed1 = LINEAR_SPEED;
	double rotSpeed1 = ROTATE_SPEED;
	double linSpeed2 = LINEAR_SPEED;
	double rotSpeed2 = ROTATE_SPEED;

	int option = Menu::runMenu();

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Andy 500"); // opens the window

																		//timer
	sf::Font font;
	font.loadFromFile("INVASION2000.TTF");
	sf::Text timer;
	timer.setFont(font);
	timer.setCharacterSize(400);
	timer.setPosition(sf::Vector2f(window.getSize().x / 2 - 200, window.getSize().y / 2 - 200));
	timer.setString("5");
	char time[5];

	//laps
	sf::Text laps1;
	sf::Text laps2;
	laps1.setFont(font);
	laps1.setCharacterSize(40);
	laps1.setPosition(900, 700);
	laps1.setString("Player 1 Laps: 0");

	laps2.setFont(font);
	laps2.setCharacterSize(40);
	laps2.setPosition(900, 760);
	laps2.setString("Player 2 Laps: 0");


	sf::Texture redCar;
	sf::Texture blueCar;
	sf::Texture trackTxtr;
	redCar.loadFromFile("redCar.png");
	blueCar.loadFromFile("blueCar.png");
	trackTxtr.loadFromFile("Track.png");


	sf::Image trackImg;
	trackImg.loadFromFile("Track.png");
	sf::Sprite track(trackTxtr); // sets the backround to the Track.png

	Car car1(sf::Vector2f(1100, 125), &redCar);
	Car car2(sf::Vector2f(1100, 65), &blueCar);

	bool keys1[4] = { false };
	bool keys2[4] = { false };
	bool lapFlags1[2] = { false };
	bool lapFlags2[2] = { false };
	int lapCount1 = 0, lapCount2 = 0;

	/****TIMER Before Game Starts****/
	for (int i = 1000; i >= 0; i--)
	{
		if (i % 200 == 0)
		{
			itoa(i / 200, time, 10);
			timer.setString((std::string)time);
		}
		window.clear();
		window.draw(track);
		window.draw(car1);
		if (option == 2)
			window.draw(car2);
		window.draw(timer);
		window.display();
	}
	/********************************/

	while (window.isOpen()) // keep the program running as long as the window is not closed by the user
	{
		sf::Event event;
		while (window.pollEvent(event)) // iterate through when user interface is detected (closing, key press, etc.)
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) // turn left
		{
			keys1[0] = true;
			keys1[1] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) // turn right
		{
			keys1[1] = true;
			keys1[0] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else
		{
			keys1[0] = false;
			keys1[1] = false;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{// move forwards 
			keys1[2] = true;
			keys1[3] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) // move backwards
		{
			keys1[3] = true;
			keys1[2] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else
		{
			keys1[2] = false;
			keys1[3] = false;
		}

		if (option == 2)
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) // turn left
			{
				keys2[0] = true;
				keys2[1] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) // turn right
			{
				keys2[1] = true;
				keys2[0] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
			}
			else
			{
				keys2[0] = false;
				keys2[1] = false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			{// move forwards 
				keys2[2] = true;
				keys2[3] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
			}
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) // move backwards
			{
				keys2[3] = true;
				keys2[2] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
			}
			else
			{
				keys2[2] = false;
				keys2[3] = false;
			}
		}


		int collision1 = car1.detectCollision(); // detects collision of car, see car.h for return values

		if (collision1 == 2)
			lapFlags1[0] = true;
		if (collision1 == 3)
			lapFlags1[1] = true;

		if (lapFlags1[1] && !lapFlags1[0])
			lapFlags1[1] = false;

		if (lapFlags1[0] && lapFlags1[1])
		{
			char l1[5];
			char name1[20] = "Player 1 Laps: ";
			lapCount1++;
			itoa(lapCount1, l1, 10);
			laps1.setString((std::string)strcat(name1, l1));
			lapFlags1[0] = lapFlags1[1] = false;
		}

		if (lapFlags1[0] && lapFlags1[1])
		{
			lapCount1++;
			lapFlags1[0] = lapFlags1[1] = false;
		}
		if (keys1[0]) // turn left
		{

			if (collision1 == 1)
			{
				linSpeed1 *= PENALTY;
				rotSpeed1 *= PENALTY;
			}

			car1.rotate(-rotSpeed1);
			linSpeed1 = LINEAR_SPEED;
			rotSpeed1 = ROTATE_SPEED;
		}

		if (keys1[1]) // turn right
		{
			if (collision1 == 1)
			{
				linSpeed1 *= PENALTY;
				rotSpeed1 *= PENALTY;
			}

			car1.rotate(rotSpeed1);
			linSpeed1 = LINEAR_SPEED;
			rotSpeed1 = ROTATE_SPEED;
		}

		if (keys1[2]) //- movement obtained from: https://en.sfml-dev.org/forums/index.php?topic=4951.0
		{
			if (collision1 == 1)
			{
				linSpeed1 *= PENALTY;
				rotSpeed1 *= PENALTY;
			}

			car1.move(sf::Vector2f(-linSpeed1 * cos(3.14159265 * (car1.getRotation() - 180) / 180),
				-linSpeed1 * sin(3.14159265 * (car1.getRotation() - 180) / 180)));
			linSpeed1 = LINEAR_SPEED;
			rotSpeed1 = ROTATE_SPEED;
		}

		if (keys1[3]) // this movement speed is divided by 2 to move slower when moving backwards
		{
			if (collision1 == 1)
			{
				linSpeed1 *= PENALTY;
				rotSpeed1 *= PENALTY;
			}

			car1.move(sf::Vector2f((linSpeed1 / 2) * cos(3.14159265 * (car1.getRotation() - 180) / 180),
				(linSpeed1 / 2) * sin(3.14159265 * (car1.getRotation() - 180) / 180)));
			linSpeed1 = LINEAR_SPEED;
			rotSpeed1 = ROTATE_SPEED;
		}

		if (option == 2)
		{
			int collision2 = car2.detectCollision();

			if (collision2 == 2)
				lapFlags2[0] = true;
			if (collision2 == 3)
				lapFlags2[1] = true;

			if (lapFlags2[1] && !lapFlags2[0])
				lapFlags2[1] = false;

			if (lapFlags2[0] && lapFlags2[1])
			{
				char l2[5];
				char name2[20] = "Player 2 Laps: ";
				lapCount2++;
				itoa(lapCount2, l2, 10);
				laps2.setString((std::string)strcat(name2, l2));
				lapFlags2[0] = lapFlags2[1] = false;
			}

			if (keys2[0]) // turn left
			{

				if (collision2 == 1)
				{
					linSpeed2 *= PENALTY;
					rotSpeed2 *= PENALTY;
				}

				car2.rotate(-rotSpeed2);
				linSpeed2 = LINEAR_SPEED;
				rotSpeed2 = ROTATE_SPEED;
			}

			if (keys2[1]) // turn right
			{
				if (collision2 == 1)
				{
					linSpeed2 *= PENALTY;
					rotSpeed2 *= PENALTY;
				}

				car2.rotate(rotSpeed2);
				linSpeed2 = LINEAR_SPEED;
				rotSpeed2 = ROTATE_SPEED;
			}

			if (keys2[2]) //- movement obtained from: https://en.sfml-dev.org/forums/index.php?topic=4951.0
			{
				if (collision2 == 1)
				{
					linSpeed2 *= PENALTY;
					rotSpeed2 *= PENALTY;
				}

				car2.move(sf::Vector2f(-linSpeed2 * cos(3.14159265 * (car2.getRotation() - 180) / 180),
					-linSpeed2 * sin(3.14159265 * (car2.getRotation() - 180) / 180)));
				linSpeed2 = LINEAR_SPEED;
				rotSpeed2 = ROTATE_SPEED;
			}

			if (keys2[3]) // this movement speed is divided by 2 to move slower when moving backwards
			{
				if (collision2 == 1)
				{
					linSpeed2 *= PENALTY;
					rotSpeed2 *= PENALTY;
				}

				car2.move(sf::Vector2f((linSpeed2 / 2) * cos(3.14159265 * (car2.getRotation() - 180) / 180),
					(linSpeed2 / 2) * sin(3.14159265 * (car2.getRotation() - 180) / 180)));
				linSpeed2 = LINEAR_SPEED;
				rotSpeed2 = ROTATE_SPEED;
			}
		}

		window.clear(); // mandatory to do before drawing stuff, so that shape doesn't actually get covered
		window.draw(track);
		window.draw(laps1);
		if (option == 2)
			window.draw(laps2);
		window.draw(car1); // this goes to a hidden buffer - display will copy this to the main buffer
		if (option == 2)
			window.draw(car2);
		window.display(); // copies the hidden buffer to the main buffer (window) - this is double-buffering

		if (lapCount1 == 3 || lapCount2 == 3)
		{
			window.close();
		}
	}

	(lapCount2 == 3 ? std::cout << "PLAYER 2" : std::cout << "PLAYER 1") << " WINS!!!!!!!!!!!!111!!!!!1" << std::endl;
	system("pause");

	return 0;

}
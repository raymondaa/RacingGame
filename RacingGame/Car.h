#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"

class Car : public sf::RectangleShape
{
public:
	enum position //allows to keep track of what position each coordinate corresponds to on the car
	{
		topLeft = 0,
		topRight = 1,
		botRight = 2,
		botLeft = 3
	};

	sf::Vector2f coords[4]; //collision checking

	Car(sf::Vector2f &pos, const sf::Texture * newTexture) //Dont have Texture for car to make sprite yet.
	{
		this->setSize(sf::Vector2f(100, 40)); //hardcoded value of car as that is how big the car textures are
		this->setTexture(newTexture);
		this->setPosition(pos);
		track.loadFromFile("Track.png");

		coords[topLeft] = pos;
		coords[topRight].x = pos.x + getSize().x;
		coords[topRight].y = pos.y;
		coords[botRight].x = pos.x + getSize().x;
		coords[botRight].y = pos.y + getSize().y;
		coords[botLeft].x = pos.x;
		coords[botLeft].y = pos.y + getSize().y;
	}

	int detectCollision(); // returns 1 if in grass, 0 if on track
						   // 2 if passing bottom track check point, 3 if top track checkpoint

private:
	sf::Image track;

};

int Car::detectCollision()
{
	sf::Color grassColor(22, 172, 82, 255);
	sf::Color temp;
	bool flag = false;

	//have to update the position of the coordinates around the car each time
	sf::Vector2f pos = getPosition();
	coords[topLeft] = pos;
	coords[topRight].x = pos.x + getSize().x * cos(3.14159265 * (getRotation()) / 180);
	coords[topRight].y = pos.y + getSize().x * sin(3.14159265 * (getRotation()) / 180);
	coords[botRight].x = coords[topRight].x - getSize().y * sin(3.14159265 * (getRotation()) / 180);
	coords[botRight].y = coords[topRight].y + getSize().y * cos(3.14159265 * (getRotation()) / 180);
	coords[botLeft].x = pos.x - getSize().y * sin(3.14159265 * (getRotation()) / 180);
	coords[botLeft].y = pos.y + getSize().y * cos(3.14159265 * (getRotation()) / 180);

	//std::cout << "(" << pos.x << ", " << pos.y << ")" << std::endl;

	for (int i = 0; i < 4; i++)
	{
		if (coords[i].x <= 0)
		{
			setPosition(sf::Vector2f(coords[i].x + 100, coords[i].y));
			flag = true;
		}

		if (coords[i].y <= 0)
		{
			setPosition(sf::Vector2f(coords[i].x, coords[i].y + 100));
			flag = true;
		}

		if (coords[i].x >= SCREEN_X)
		{
			setPosition(sf::Vector2f(coords[i].x - 100, coords[i].y));
			flag = true;
		}

		if (coords[i].y >= SCREEN_Y)
		{
			setPosition(sf::Vector2f(coords[i].x, coords[i].y - 100));
			flag = true;
		}

		if (flag)
		{
			coords[topLeft] = pos;
			coords[topRight].x = pos.x + getSize().x * cos(3.14159265 * (getRotation()) / 180);
			coords[topRight].y = pos.y + getSize().x * sin(3.14159265 * (getRotation()) / 180);
			coords[botRight].x = coords[topRight].x - getSize().y * sin(3.14159265 * (getRotation()) / 180);
			coords[botRight].y = coords[topRight].y + getSize().y * cos(3.14159265 * (getRotation()) / 180);
			coords[botLeft].x = pos.x - getSize().y * sin(3.14159265 * (getRotation()) / 180);
			coords[botLeft].y = pos.y + getSize().y * cos(3.14159265 * (getRotation()) / 180);
		}

		temp = track.getPixel(coords[i].x, coords[i].y);

		if (pos.x >= 800 && pos.x <= 810 && pos.y >= 900 && pos.y <= 1050)
			return 2;

		if (pos.x >= 1035 && pos.x <= 1060 && pos.y <= 162 && pos.y >= 30)
			return 3;

		if (temp == grassColor)
			return 1;
	}

	return 0;

}
#ifndef _CANNON_H
#define _CANNON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Seed.h"

#define BARRELCOLOR sf::Color(128, 32, 64, 255)
#define STANDCOLOR sf::Color(192, 96, 64, 255)
#define MAXPOWER 37.5f
#define DEFAULTPOWER 7.5f

class Cannon : public GameEntity
{
private:
	std::vector<Seed*> _seeds;
	float _angle, _power;
	sf::Vector2f shootSpot;
	bool _pressed, _shoot;

	sf::RectangleShape* _barrel;
	sf::ConvexShape* _stand;

public:
	void Shoot(sf::Vector2f MousePos, b2World& World, float Power);

	void ProcessInput(sf::Event Event);
	void Update(sf::Vector2f MousePos, float WindStrength, b2World& World);
	void Draw(sf::RenderWindow* Window);

	Cannon();
	Cannon(sf::Vector2f Position, b2World& World);
	~Cannon();
};

#endif

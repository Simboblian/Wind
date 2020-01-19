#ifndef _CANNON_H
#define _CANNON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "UIProgressBar.h"
#include "Seed.h"

#define BARRELCOLOR sf::Color(128, 32, 64, 255)
#define STANDCOLOR sf::Color(192, 96, 64, 255)
#define POWERCOLOR sf::Color(255, 0, 0, 255)
#define PREVIOUSPOWERCOLOR sf::Color(128, 128, 128, 255)
#define POWERMETERPOS sf::Vector2f(0.0f, -40.0f)
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

	UIProgressBar* _powerMeter;
	UIProgressBar* _previousPowerMeter;
public:
	void Shoot(sf::Vector2f MousePos, b2World& World, float Power);

	void ProcessInput(sf::Event Event);
	void Update(sf::Vector2f MousePos, float WindStrength, b2World& World);
	void Draw(sf::RenderWindow& Window);

	Cannon();
	Cannon(sf::Vector2f Position, b2World& World);
	~Cannon();
};

#endif

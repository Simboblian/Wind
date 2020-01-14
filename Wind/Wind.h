#ifndef _WIND_H
#define _WIND_H

#include <iostream>
#include "Blossom.h"

#define LERPSPEED 0.05f
#define BLOSSOMRADIUS 2.5f
#define SUMMONRATE 20.0f //Less is faster here
#define DIRECTIONCHANGERATE 600.0f

class Wind
{
private:
	float _targetStrength, _strength;
	int _directionCounter, _summonCounter, _summon;

	std::vector<Blossom*> _blossoms;
public:
	float GetStrength() { return _strength; };

	void RandomizeStrength() { _targetStrength = (float)((rand() %100 - 50)) / 5; };
	
	void Update(sf::Vector2f WindowSize, sf::Vector2f WindowPos, b2World& World);
	void Draw(sf::RenderWindow* Window);

	Wind(sf::Vector2f WindowSize, sf::Vector2f WindowPos, b2World& World);
	Wind();
	~Wind();
};

#endif
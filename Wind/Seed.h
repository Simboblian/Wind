#ifndef _SEED_H
#define _SEED_H

#include "GameEntity.h"

#define TTL 600
#define SEEDCOLOR sf::Color(160, 64, 64, 255)

class Seed : public GameEntity
{
private:
	sf::CircleShape* _shape;

	int _timeToLive, _lifeCounter;
public:
	bool BulletUpdate(sf::Vector2f WindStrength);
	void Draw(sf::RenderWindow& Window);

	Seed(float SeedSize, b2World& World);
	Seed();
	~Seed();
};

#endif
#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "GameEntity.h"

#define PARTICLECOLOR sf::Color(251, 212, 236, 255)
#define TTL 10000

class Particle : public GameEntity
{
private:
	sf::CircleShape* _shape;

	int _timeToLive, _lifeCounter;

	void CheckTTL();
public:
	void SetPosition(sf::Vector2f Position);
	void SetColor(sf::Color Color) { _shape->setFillColor(Color); };

	sf::CircleShape* GetShape() { return _shape; };

	void Update();
	void Update(float Strength);
	void Update(sf::Vector2f WindStrength);
	void Draw(sf::RenderWindow &Window);

	Particle(float Radius, b2World& World, int TimeToLive = TTL);
	Particle();
	~Particle();
};

#endif
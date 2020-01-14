#include "Seed.h"

bool Seed::BulletUpdate(sf::Vector2f WindStrength)
{
	GetBody()->ApplyForceToCenter(Utility::SFVECtoB2VEC(WindStrength, true), true);
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));

	return (++_lifeCounter > _timeToLive);
}

void Seed::Draw(sf::RenderWindow* Window)
{
	Window->draw(*_shape);
}

Seed::Seed(float SeedSize, b2World& World)
{
	_timeToLive = TTL;
	_lifeCounter = 0;

	_shape = new sf::CircleShape(SeedSize, 20);
	_shape->setOrigin(SeedSize, SeedSize);
	_shape->setFillColor(SEEDCOLOR);
	CreateCircularBody(World, Utility::ScaleToB2(SeedSize));
}

Seed::Seed()
{
}

Seed::~Seed()
{
}

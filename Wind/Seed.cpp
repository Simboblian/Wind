#include "Seed.h"

bool Seed::BulletUpdate(sf::Vector2f WindStrength)
{
	GetBody()->ApplyForceToCenter(Utility::SFVECtoB2VEC(WindStrength, true), true);
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));

	return (++_lifeCounter > _timeToLive);
}

void Seed::Draw(sf::RenderWindow& Window)
{
	Window.draw(*_shape);
}

Seed::Seed(float SeedSize, b2World& World)
{
	_timeToLive = TTL;
	_lifeCounter = 0;

	_shape = new sf::CircleShape(SeedSize, 20);
	_shape->setOrigin(SeedSize, SeedSize);
	_shape->setFillColor(SEEDCOLOR);
	CreateCircularBody(World, Utility::ScaleToB2(SeedSize), b2BodyType::b2_dynamicBody);
	GetBody()->SetBullet(true);
	GetBody()->SetUserData((void*)ut::SEED);
	GetBody()->GetFixtureList()[0].SetRestitution(0.5);

	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
}

Seed::Seed()
{
}

Seed::~Seed()
{
}

#include "Particle.h"

void Particle::CheckTTL()
{
	if (++_lifeCounter > _timeToLive)
	{
		GetBody()->SetUserData((void*)ut::DEAD);
	}
}

void Particle::SetPosition(sf::Vector2f Position)
{
	GetBody()->SetTransform(Utility::SFVECtoB2VEC(Position, true), 0.0f);
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
}

void Particle::Update()
{
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
	CheckTTL();
}

void Particle::Update(float Strength)
{
	GetBody()->SetLinearVelocity(b2Vec2(Strength, 0.5));
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
	CheckTTL();
}

void Particle::Update(sf::Vector2f WindStrength)
{
	sf::Vector2f CurrentVelocity = Utility::B2VECtoSFVEC(GetBody()->GetLinearVelocity(), false);
	float impulseX = GetBody()->GetMass() * (WindStrength.x - CurrentVelocity.x);
	float impulseY = GetBody()->GetMass() * (WindStrength.y - CurrentVelocity.y);

	GetBody()->ApplyLinearImpulseToCenter(Utility::SFVECtoB2VEC(sf::Vector2f(impulseX / 10, 0), true), true);
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
	CheckTTL();
}

void Particle::Draw(sf::RenderWindow& Window)
{
	Window.draw(*_shape);
}

Particle::Particle(float Radius, b2World& World, int TimeToLive)
{
	_timeToLive = TimeToLive;
	_lifeCounter = 0;

	_shape = new sf::CircleShape(Radius, 20);
	_shape->setOrigin(Radius, Radius);
	_shape->setFillColor(PARTICLECOLOR);
	CreateCircularBody(World, Utility::ScaleToB2(Radius), b2BodyType::b2_dynamicBody);
	GetBody()->GetFixtureList()[0].SetSensor(true);
	GetBody()->SetGravityScale(0);
}

Particle::Particle()
{
}

Particle::~Particle()
{
}

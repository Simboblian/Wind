#include "Blossom.h"

void Blossom::SetPosition(sf::Vector2f Position)
{
	GetBody()->SetTransform(Utility::SFVECtoB2VEC(Position, true), 0.0f);
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
}

void Blossom::Update(float Strength)
{
	GetBody()->SetLinearVelocity(b2Vec2(Strength, 0.5));
	_shape->setPosition(Utility::B2VECtoSFVEC(GetBody()->GetPosition(), true));
}

void Blossom::Draw(sf::RenderWindow& Window)
{
	Window.draw(*_shape);
}

Blossom::Blossom(float Radius, b2World& World)
{
	_shape = new sf::CircleShape(Radius, 20);
	_shape->setOrigin(Radius, Radius);
	_shape->setFillColor(BLOSSOMCOLOR);
	CreateCircularBody(World, Utility::ScaleToB2(Radius), b2BodyType::b2_dynamicBody);
	GetBody()->GetFixtureList()[0].SetSensor(true);
	GetBody()->SetGravityScale(0);
}

Blossom::Blossom()
{
}

Blossom::~Blossom()
{
}

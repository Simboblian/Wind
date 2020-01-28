#include "Tree.h"

void Tree::Update()
{
}

void Tree::Draw(RenderWindow& Window)
{
	Window.draw(_sprite);
}

Tree::Tree(int Index, sf::Vector2f Size, sf::Vector2f Position, b2World& World)
{
	CreateSquareBody(World, Size, b2BodyType::b2_staticBody);
	GetBody()->SetTransform(Utility::SFVECtoB2VEC(Position, true), 0);
	GetBody()->SetUserData((void*)ut::TREE);
	GetBody()->GetFixtureList()[0].SetSensor(true);
	GetBody()->SetGravityScale(0);

	_texture.loadFromFile("Resources/Images/Trees.png");
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, (rand() % 4) * 32, 32, 32));
	_sprite.setPosition(Position.x, Position.y+ 16);
	_sprite.setOrigin(sf::Vector2f(16, 32));
}

Tree::Tree()
{
}

Tree::~Tree()
{
}

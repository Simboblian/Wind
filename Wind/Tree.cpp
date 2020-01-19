#include "Tree.h"

void Tree::Update()
{
}

void Tree::Draw()
{
}

Tree::Tree(int Index, sf::Vector2f Size, sf::Vector2f Position, b2World& World)
{
	CreateSquareBody(World, Size);
	GetBody()->SetTransform(Utility::SFVECtoB2VEC(Position, true), 0);
	GetBody()->SetUserData((void*)ut::TREE);
}

Tree::Tree()
{
}

Tree::~Tree()
{
}

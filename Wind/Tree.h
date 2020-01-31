#ifndef _TREE_H
#define _TREE_H

#include "GameEntity.h"
#include "Particle.h"
#include <iostream>

#define TRUNKCOLOR sf::Color(160, 64, 64, 255)
#define FOLIAGECOLOR1 sf::Color(160, 192, 64, 255)
#define FOLIAGECOLOR2 sf::Color(130, 172, 64, 255)
#define FOLIAGECOLOR3 sf::Color(100, 152, 64, 255)
#define FOLIAGECOLOR4 sf::Color(70, 132, 64, 255)
#define FOLIAGECOLOR5 sf::Color(40, 112, 64, 255)

class Tree : public GameEntity
{
private:
	int _index, _value, _level;
	float _multiplier;
	string _oldType;

	std::vector<sf::ConvexShape*> _shapes;
	std::vector<Particle*> _particles;
public:
	void Update();
	void Draw(RenderWindow& Window);

	int GetValue() { return _value; };
	void CalculateMultiplier(sf::Vector2f WindowSize, sf::Vector2f WindowPos);

	Tree(int Index, sf::Vector2f Size, sf::Vector2f Position, b2World& World);
	Tree();
	~Tree();
};

#endif
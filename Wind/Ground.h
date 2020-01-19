#ifndef _GROUND_H
#define _GROUND_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "SFMLDebugDraw.h"
#include "Tree.h"
#include "Utility.h"

#define GROUNDCOLOR sf::Color(96, 160, 64, 255)

class Ground
{
private:
	b2Body* _groundBody;
	float _angle;
	float _magnitude;
	
	sf::Vector2f _cannonPos;

	std::vector<sf::ConvexShape*> _groundShapes;
	std::vector<Tree*> _trees;

	void PopulateGroundShape(sf::Vector2f FirstPoint, sf::Vector2f SecondPoint, sf::Vector2f WindowPos, sf::Vector2f WindowSize);
	sf::Vector2f NewPosition(sf::Vector2f currentPos);
public:
	void SummonTree(int Type, sf::Vector2f Position, b2World& World);
	sf::Vector2f GetCannonPos() { return _cannonPos; };
	void Draw(sf::RenderWindow& Window);

	Ground();
	Ground(sf::Vector2f windowSize, sf::Vector2f windowPos, b2World& World);
	~Ground();
};

#endif
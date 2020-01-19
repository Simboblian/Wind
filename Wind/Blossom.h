#ifndef _BLOSSOM_H
#define _BLOSSOM_H

#include "GameEntity.h"

#define BLOSSOMCOLOR sf::Color(224, 224, 128, 255)

class Blossom : public GameEntity
{
private:
	sf::CircleShape* _shape;
public:
	void SetPosition(sf::Vector2f Position);

	void Update(float Strength);
	void Draw(sf::RenderWindow &Window);

	Blossom(float Radius, b2World& World);
	Blossom();
	~Blossom();
};

#endif
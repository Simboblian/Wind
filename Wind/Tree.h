#ifndef _TREE_H
#define _TREE_H

#include "GameEntity.h"

class Tree : public GameEntity
{
private:
	int _index;

	sf::Texture _texture;
	sf::Sprite _sprite;


public:
	void Update();
	void Draw();

	Tree(int Index, sf::Vector2f Size, sf::Vector2f Position, b2World& World);
	Tree();
	~Tree();
};

#endif
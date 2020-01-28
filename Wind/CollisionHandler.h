#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <iostream>
#include <Box2D/Box2D.h>
#include "utility.h"
#include "GameEntity.h"

struct Collision
{
	sf::Vector2f _position;
	std::string _type;
	std::vector<b2Body*> _collidingEntities;
};

class CollisionHandler : public b2ContactListener
{
private:
	sf::Vector2f _position;

	std::vector<Collision*> CollisionList;
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	std::vector<Collision*>& GetCollisions() { return CollisionList; }
	CollisionHandler();
	~CollisionHandler();
};

#endif

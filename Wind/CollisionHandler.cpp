#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact * contact)
{
	b2Fixture* _fixtureA = contact->GetFixtureA();
	b2Fixture* _fixtureB = contact->GetFixtureB();

	if (_fixtureA->GetBody()->GetUserData() == (void*)ut::SEED)
	{
		if (_fixtureB->GetBody()->GetUserData() == (void*)ut::GRND)
		{
			_fixtureA->GetBody()->SetUserData((void*)ut::DEAD);

			Collision* collision = new Collision();
			collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localPoint, true);
			collision->_type = ut::GRND;

			CollisionList.push_back(collision);
		}
		else if (_fixtureB->GetBody()->GetUserData() == (void*)ut::TREE)
		{
			_fixtureA->GetBody()->SetUserData((void*)ut::DEAD);

			Collision* collision = new Collision();
			collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localPoint, true);
			collision->_type = ut::TREE;

			CollisionList.push_back(collision);
		}
	}

	//Then same as above but A is B ya know?

	if (_fixtureB->GetBody()->GetUserData() == (void*)ut::SEED)
	{
		if (_fixtureA->GetBody()->GetUserData() == (void*)ut::GRND)
		{
			_fixtureB->GetBody()->SetUserData((void*)ut::DEAD);

			Collision* collision = new Collision();
			collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localPoint, true);
			collision->_type = ut::GRND;

			CollisionList.push_back(collision);
		}
		else if (_fixtureA->GetBody()->GetUserData() == (void*)ut::TREE)
		{
			_fixtureB->GetBody()->SetUserData((void*)ut::DEAD);

			Collision* collision = new Collision();
			collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localPoint, true);
			collision->_type = ut::TREE;

			CollisionList.push_back(collision);
		}
	}
}

void CollisionHandler::EndContact(b2Contact * contact)
{
}

void CollisionHandler::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void CollisionHandler::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}

CollisionHandler::CollisionHandler()
{
	_position = sf::Vector2f(0, 0);
}

CollisionHandler::~CollisionHandler()
{
}

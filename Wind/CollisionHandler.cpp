#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact * contact)
{
	b2Fixture* _fixtureA = contact->GetFixtureA();
	b2Fixture* _fixtureB = contact->GetFixtureB();

	if (_fixtureA->GetBody()->GetUserData() == (void*)ut::SEED && _fixtureB->GetBody()->GetUserData() == (void*)ut::GRND)
	{
		_fixtureA->GetBody()->SetUserData((void*)ut::DEAD);

		Collision* collision = new Collision();
		collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localNormal, true);

		CollisionList.push_back(collision);

		std::cout << "Body A: " << _fixtureA->GetBody()->GetTransform().p.x << ", " << _fixtureA->GetBody()->GetTransform().p.y << std::endl;
		std::cout << "Body B: " << _fixtureB->GetBody()->GetTransform().p.x << ", " << _fixtureB->GetBody()->GetTransform().p.y << std::endl;
		std::cout << "Contact: " << collision->_position.x << ", " << collision->_position.y << std::endl;
	}

	if (_fixtureA->GetBody()->GetUserData() == (void*)ut::GRND && _fixtureB->GetBody()->GetUserData() == (void*)ut::SEED)
	{
		_fixtureB->GetBody()->SetUserData((void*)ut::DEAD);
		Collision* collision = new Collision();
		collision->_position = Utility::B2VECtoSFVEC(contact->GetManifold()->localNormal, true);

		CollisionList.push_back(collision);

		std::cout << "Body A: " << _fixtureA->GetBody()->GetTransform().p.x << ", " << _fixtureA->GetBody()->GetTransform().p.y << std::endl;
		std::cout << "Body B: " << _fixtureB->GetBody()->GetTransform().p.x << ", " << _fixtureB->GetBody()->GetTransform().p.y << std::endl;
		std::cout << "Contact: " << collision->_position.x << ", " << collision->_position.y << std::endl;
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

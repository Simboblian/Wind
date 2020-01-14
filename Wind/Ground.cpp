#include "Ground.h"

void Ground::PopulateGroundShape(sf::Vector2f FirstPoint, sf::Vector2f SecondPoint, sf::Vector2f WindowPos, sf::Vector2f WindowSize)
{
	sf::ConvexShape* groundShape = new sf::ConvexShape(4);
	groundShape->setFillColor(GROUNDCOLOR);
	groundShape->setPoint(0, FirstPoint);
	groundShape->setPoint(1, SecondPoint);
	groundShape->setPoint(2, sf::Vector2f(SecondPoint.x, WindowPos.y + (WindowSize.y / 2)));
	groundShape->setPoint(3, sf::Vector2f(FirstPoint.x, WindowPos.y + (WindowSize.y / 2)));
	_groundShapes.push_back(groundShape);
}

sf::Vector2f Ground::NewPosition(sf::Vector2f currentPos)
{
	float adjustment = _angle; //adjust this based on how up/down the current angle is;
	float newAngle = rand() % 180 - adjustment; 
	_angle += newAngle;

	sf::Vector2f newPosition;

	float x = sin(Utility::DEGTORAD(_angle)) * _magnitude;
	float y = cos(Utility::DEGTORAD(_angle)) * _magnitude;

	newPosition.x = currentPos.x + x;
	newPosition.y = currentPos.y + y;

	return newPosition;
}

void Ground::Draw(sf::RenderWindow* Window)
{
	for (int i = 0; i < _groundShapes.size(); i++)
		Window->draw(*_groundShapes[i]);
}

Ground::Ground()
{
}

Ground::Ground(sf::Vector2f WindowSize, sf::Vector2f WindowPos, b2World& World)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(Utility::ScaleToB2(WindowPos.x), Utility::ScaleToB2(WindowPos.y));

	_groundBody = World.CreateBody(&bodyDef);

	b2EdgeShape shape;

	float x = WindowPos.x - (WindowSize.x / 2);
	float y = WindowPos.y + (WindowSize.y / 4);

	sf::Vector2f pos1 = sf::Vector2f(x, y);
	sf::Vector2f pos2 = sf::Vector2f(x, y);

	_angle = 0;
	_magnitude = 10;

	//Create flat ground for seed cannon
	pos2 = sf::Vector2f(pos1.x + 50, pos1.y);
	
	//create the shapes for filling the ground;
	PopulateGroundShape(pos1, pos2, WindowPos, WindowSize);

	_cannonPos = sf::Vector2f(pos2.x - 25, pos2.y - 25);

	shape.Set(Utility::SFVECtoB2VEC(pos1, true), Utility::SFVECtoB2VEC(pos2, true));

	b2FixtureDef fixDef;
	fixDef.shape = &shape;
	_groundBody->CreateFixture(&fixDef);


	//random terrain from here
	while (pos2.x < (WindowPos.x + (WindowSize.x / 2))) 
	{
		_magnitude = rand() % 10 + 10;

		pos1 = pos2;
		pos2 = NewPosition(pos1);
		if (pos2.y > (WindowPos.y + (WindowSize.y / 2)))
			pos2.y = (WindowPos.y + (WindowSize.y / 2));

		PopulateGroundShape(pos1, pos2, WindowPos, WindowSize);

		shape.Set(Utility::SFVECtoB2VEC(pos1, true), Utility::SFVECtoB2VEC(pos2, true));

		b2FixtureDef fixDef;
		fixDef.shape = &shape;
		_groundBody->CreateFixture(&fixDef);
	}
}

Ground::~Ground()
{
}

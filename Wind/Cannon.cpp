#include "Cannon.h"

void Cannon::Shoot(sf::Vector2f MousePos, b2World& World, float Power)
{
	Seed* seed = new Seed(5, World);
	seed->SetPosition(GetPosition());
	seed->GetBody()->SetBullet(true);
	seed->GetBody()->SetGravityScale(10);
	//seed->GetBody()->GetFixtureList()[0].SetDensity(0.01);

	sf::Vector2f impulse;
	impulse = sf::Vector2f((MousePos.x - GetPosition().x) / 25, (MousePos.y - GetPosition().y) / 25);
	impulse = Utility::SetLength(impulse, Power);
	
	seed->GetBody()->ApplyLinearImpulseToCenter(Utility::SFVECtoB2VEC(impulse, true), true);
	_seeds.push_back(seed);
}

void Cannon::ProcessInput(sf::Event Event)
{
	if (Mouse::isButtonPressed(sf::Mouse::Left))
		_pressed = true;

	if (!Mouse::isButtonPressed(sf::Mouse::Left) && _pressed)
	{
		_pressed = false;
		_shoot = true;
	}
}

void Cannon::Update(sf::Vector2f MousePos, float WindStrength, b2World& World)
{
	_angle = Utility::AngleBetweenTwoVectors(GetPosition(), MousePos);

	GetBody()->SetTransform(GetBody()->GetPosition(), _angle);

	for (int i = 0; i < _seeds.size(); i++)
	{
		if (_seeds[i]->BulletUpdate(sf::Vector2f(WindStrength, 0)))
		{
			_seeds[i]->GetBody()->DestroyFixture(&_seeds[i]->GetBody()->GetFixtureList()[0]);
			delete _seeds[i];
			_seeds.erase(_seeds.begin() + i);

			if (_seeds.size() == 0)
				break;
		}
	}

	if (_pressed)
	{
		_power += 0.5;
		if (_power > MAXPOWER)
			_power = MAXPOWER;
	}
	else
	{
		if (_shoot)
		{
			_shoot = false;
			Shoot(MousePos, World, _power + DEFAULTPOWER);
		}
		_power = 0.0f;
	}

	_barrel->setRotation(Utility::RADTODEG(GetBody()->GetAngle()));
}

void Cannon::Draw(sf::RenderWindow* Window)
{
	for (int i = 0; i < _seeds.size(); i++)
	{
		_seeds[i]->Draw(Window);
	}
	Window->draw(*_barrel);
	Window->draw(*_stand);
}

Cannon::Cannon()
{
}

Cannon::Cannon(sf::Vector2f Position, b2World& World)
{
	CreateSquareBody(World, sf::Vector2f(1.25, 0.5));
	SetPosition(Position);
	GetBody()->SetGravityScale(0);
	GetBody()->GetFixtureList()[0].SetSensor(true);

	_barrel = new sf::RectangleShape();
	_barrel->setFillColor(BARRELCOLOR);
	_barrel->setSize(Utility::B2VECtoSFVEC(b2Vec2(1.25, 0.5), true));
	_barrel->setPosition(Position);
	_barrel->setOrigin(_barrel->getSize().x / 2, _barrel->getSize().y / 2);

	_stand = new sf::ConvexShape(3);
	_stand->setFillColor(STANDCOLOR);
	_stand->setPoint(0, Position);
	_stand->setPoint(1, sf::Vector2f(Position.x - 12.5, Position.y + 25));
	_stand->setPoint(2, sf::Vector2f(Position.x + 12.5, Position.y + 25));


}

Cannon::~Cannon()
{
}

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
			_previousPowerMeter->SetCurrent(_power);
		}
		_power = 0.0f;
	}

	for (int i = 0; i < _seeds.size(); i++)
	{
		if (_seeds[i]->BulletUpdate(sf::Vector2f(WindStrength, 0)) || _seeds[i]->GetBody()->GetUserData() == (void*)ut::DEAD)
		{
			_seeds[i]->GetBody()->DestroyFixture(&_seeds[i]->GetBody()->GetFixtureList()[0]);
			delete _seeds[i];
			_seeds.erase(_seeds.begin() + i);

			if (_seeds.size() == 0)
				break;
		}
	}

	_powerMeter->SetColour(sf::Color(min((_power / MAXPOWER) * 1020, 255.0f), 255 - ((_power / MAXPOWER) * 255), 0, 255));
	_powerMeter->SetCurrent(_power);
	_powerMeter->Update(sf::Vector2f(GetPosition().x + POWERMETERPOS.x, GetPosition().y + POWERMETERPOS.y));
	_previousPowerMeter->Update(sf::Vector2f(GetPosition().x + POWERMETERPOS.x, GetPosition().y + POWERMETERPOS.y));
	_barrel->setRotation(Utility::RADTODEG(GetBody()->GetAngle()));
}

void Cannon::Draw(sf::RenderWindow& Window)
{
	_previousPowerMeter->Draw(Window);
	_powerMeter->Draw(Window);

	for (int i = 0; i < _seeds.size(); i++)
	{
		_seeds[i]->Draw(Window);
	}

	Window.draw(*_barrel);
	Window.draw(*_stand);
}

Cannon::Cannon()
{
}

Cannon::Cannon(sf::Vector2f Position, b2World& World)
{
	CreateSquareBody(World, sf::Vector2f(1.25, 0.5), b2BodyType::b2_dynamicBody);
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

	_powerMeter = new UIProgressBar(sf::Vector2f(Position.x + POWERMETERPOS.x, Position.y + POWERMETERPOS.y), sf::Vector2f(45, 8));
	_powerMeter->SetMax(MAXPOWER);
	_powerMeter->SetColour(POWERCOLOR);
	_powerMeter->SetCurrent(0.0f);

	_previousPowerMeter = new UIProgressBar(sf::Vector2f(Position.x + POWERMETERPOS.x, Position.y + POWERMETERPOS.y), sf::Vector2f(45, 8));
	_previousPowerMeter->SetMax(MAXPOWER);
	_previousPowerMeter->SetColour(PREVIOUSPOWERCOLOR);
	_previousPowerMeter->SetCurrent(0.0f);


}

Cannon::~Cannon()
{
}

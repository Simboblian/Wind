#include "Tree.h"

void Tree::Update()
{
	if (GetBody()->GetUserData() == (void*)ut::TRE0)
	{
		_level = 1;
		_shapes[0]->setScale(1.1f, 1.1f);
		_shapes[0]->setFillColor(FOLIAGECOLOR1);
	}
	else if(GetBody()->GetUserData() == (void*)ut::TRE1)
	{
		_level = 2;
		_shapes[0]->setScale(1.2f, 1.2f);
		_shapes[0]->setFillColor(FOLIAGECOLOR2);
	}
	else if (GetBody()->GetUserData() == (void*)ut::TRE2)
	{
		_level = 3;
		_shapes[0]->setScale(1.3f, 1.3f);
		_shapes[0]->setFillColor(FOLIAGECOLOR3);
	}
	else if (GetBody()->GetUserData() == (void*)ut::TRE3)
	{
		_level = 4;
		_shapes[0]->setScale(1.4f, 1.4f);
		_shapes[0]->setFillColor(FOLIAGECOLOR4);
	}
	else if (GetBody()->GetUserData() == (void*)ut::TRE4)
	{
		_level = 5;
		_shapes[0]->setScale(1.5f, 1.5f);
		_shapes[0]->setFillColor(FOLIAGECOLOR5);
	}

	for (int i = 0; i < _particles.size(); i++)
	{
		_particles[i]->Update();

		if (_particles[i]->GetBody()->GetUserData() == (void*)ut::DEAD)
		{
			_particles[i]->GetBody()->DestroyFixture(&_particles[i]->GetBody()->GetFixtureList()[0]);
			delete _particles[i];
			_particles.erase(_particles.begin() + i);

			if (_particles.size() == 0)
				break;
		}
	}

	_value = (_level * 10) * _multiplier;
}

void Tree::Draw(RenderWindow& Window)
{
	for (int i = 0; i < _shapes.size(); i++)
	{
		Window.draw(*_shapes[i]);
	}

	for (int i = 0; i < _particles.size(); i++)
	{
		_particles[i]->Draw(Window);
	}
}

void Tree::CalculateMultiplier(sf::Vector2f WindowSize, sf::Vector2f WindowPos)
{
	float Max = WindowPos.x + WindowSize.x;
	float Percent = (WindowSize.x / 2) - GetPosition().x;
	Percent = (Max - Percent) / Max;

	_multiplier = 1.0f + (Percent * 4);

	_value = (_level * 100) * _multiplier;
}

Tree::Tree(int Index, sf::Vector2f Size, sf::Vector2f Position, b2World& World)
{
	_index = Index;
	CreateSquareBody(World, Size, b2BodyType::b2_staticBody);
	GetBody()->SetTransform(Utility::SFVECtoB2VEC(Position, true), 0);
	GetBody()->SetUserData((void*)ut::TRE0);
	GetBody()->GetFixtureList()[0].SetSensor(true);
	GetBody()->SetGravityScale(0);

	sf::ConvexShape* foliage = new sf::ConvexShape(3);
	foliage->setPoint(0, Utility::B2VECtoSFVEC(b2Vec2(-(Size.x), 0), true));
	foliage->setPoint(1, Utility::B2VECtoSFVEC(b2Vec2(Size.x, 0), true));
	foliage->setPoint(2, Utility::B2VECtoSFVEC(b2Vec2(0, -Size.y), true));
	foliage->setFillColor(FOLIAGECOLOR1);
	foliage->setPosition(Position);
	_shapes.push_back(foliage);

	sf::ConvexShape* trunk = new sf::ConvexShape(5);
	trunk->setPoint(0, Utility::B2VECtoSFVEC(b2Vec2(-(Size.x/2), (Size.y*2)), true));
	trunk->setPoint(1, Utility::B2VECtoSFVEC(b2Vec2((Size.x / 2), (Size.y * 2)), true));
	trunk->setPoint(2, Utility::B2VECtoSFVEC(b2Vec2((Size.x / 2), 0), true));
	trunk->setPoint(3, Utility::B2VECtoSFVEC(b2Vec2(0, -(Size.y / 2)), true));
	trunk->setPoint(4, Utility::B2VECtoSFVEC(b2Vec2(-(Size.x / 2), 0), true));
	trunk->setFillColor(TRUNKCOLOR);
	trunk->setPosition(Position);
	_shapes.push_back(trunk);

	//_texture.loadFromFile("Resources/Images/Trees.png");
	//_sprite.setTexture(_texture);
	//_sprite.setTextureRect(sf::IntRect(0, _index * 64, 64, 64));
	//_sprite.setPosition(Position.x, Position.y + 16);
	//_sprite.setOrigin(sf::Vector2f(32, 64));

	for (int i = 0; i < 20; i++)
	{
		int Color = (rand() % 40 - 20);
		float Angle = Utility::DEGTORAD(rand() % 360);
		float Strength = rand() % 5 / 2.0f;
		sf::Vector2f Impulse = sf::Vector2f(sin(Angle), cos(Angle));
		Impulse = Utility::SetLength(Impulse, Strength);

		Particle* particle = new Particle(rand() % 5 + 2, World, rand() % 30 + 15);
		particle->SetPosition(GetPosition() + sf::Vector2f(Impulse.x * 10, Impulse.y * 10));
		particle->GetBody()->SetGravityScale(-3);
		particle->GetBody()->GetFixtureList()[0].SetDensity((rand() % 10 + 1) / 10.0f);
		particle->SetColor(sf::Color(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100, 255));
		particle->GetBody()->ApplyLinearImpulseToCenter(Utility::SFVECtoB2VEC(Impulse, true), true);

		_particles.push_back(particle);
	}

	_multiplier = 1.0f;
	_level = 1;
	_value = 1;
}

Tree::Tree()
{
}

Tree::~Tree()
{
}

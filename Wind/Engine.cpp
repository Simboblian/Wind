#include "Engine.h"

bool Engine::Init()
{
	srand(time(NULL));

	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Wind");
	_window->setVerticalSyncEnabled(true);

	_camera = new Camera(_window->getSize());
	_window->setView(_camera->GetCamera());
	_mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window), _camera->GetCamera());

	_world = new b2World(b2Vec2(0, 9.8f));

	_collision = new CollisionHandler;
	_world->SetContactListener(_collision);

	_ground = new Ground(_camera->GetSize(), _camera->GetPosition(), *_world);
	_wind = new Wind(_camera->GetSize(), _camera->GetPosition(), *_world);
	_cannon = new Cannon(_ground->GetCannonPos(), *_world);

	_debugDraw = new SFMLDebugDraw(*_window);
	_world->SetDebugDraw(_debugDraw);
	uint32 _flags = 0;
	//_flags += b2Draw::e_aabbBit;
	//_flags += b2Draw::e_centerOfMassBit;
	//_flags += b2Draw::e_pairBit;
	//_flags += b2Draw::e_jointBit;
	_flags += b2Draw::e_shapeBit;
	_debugDraw->SetFlags(_flags);

	_score = 0;

	if (!_font.loadFromFile("Resources/Fonts/Pacifico-Regular.ttf"))
	{
		std::cout << "Unable to Load Font!" << std::endl;
	}
	_text = new sf::Text("Score: 000000", _font, 30);
	_text->setFillColor(sf::Color::White);

	_scoreString = "Score: ";
	for (int i = 0; i < (6 - to_string(_score).length()); i++)
		_scoreString.append("0");

	_text->setString(_scoreString + to_string(_score));

	return true;
}

void Engine::MainLoop()
{
	while (_window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

void Engine::ProcessInput()
{
	sf::Event evt;

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window->close();
	}

	_cannon->ProcessInput(evt);
}

void Engine::RenderFrame()
{
	_window->clear(SKYCOLOR);

	_ground->Draw(*_window);
	_cannon->Draw(*_window);
	_wind->Draw(*_window);
	_window->draw(*_text);
	_cannon->DrawUI(*_window);
	//_world->DrawDebugData();

	_window->display();
}

void Engine::Update()
{
	_world->Step(1 / 60.0f, 8, 3);

	_camera->Update(*_window);

	_mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window), _camera->GetCamera());

	_wind->Update(_camera->GetSize(), _camera->GetPosition(), *_world);
	_cannon->Update(_mousePos, _wind->GetStrength(), *_world);

	if (_collision->GetCollisions().size() > 0)
	{
		_cannon->SetAvailable(true);
		_wind->RandomizeStrength();
		if (_collision->GetCollisions()[0]->_type == ut::TREE)
		{
			for (int i = 0; i < _collision->GetCollisions()[0]->_collidingEntities.size(); i++)
			{
				if (_collision->GetCollisions()[0]->_collidingEntities[i]->GetUserData() == (void*)ut::TRE0)
				{
					_collision->GetCollisions()[0]->_collidingEntities[i]->SetUserData((void*)ut::TRE1);
				}
				else if (_collision->GetCollisions()[0]->_collidingEntities[i]->GetUserData() == (void*)ut::TRE1)
				{
					_collision->GetCollisions()[0]->_collidingEntities[i]->SetUserData((void*)ut::TRE2);
				}
				else if (_collision->GetCollisions()[0]->_collidingEntities[i]->GetUserData() == (void*)ut::TRE2)
				{
					_collision->GetCollisions()[0]->_collidingEntities[i]->SetUserData((void*)ut::TRE3);
				}
				else if (_collision->GetCollisions()[0]->_collidingEntities[i]->GetUserData() == (void*)ut::TRE3)
				{
					_collision->GetCollisions()[0]->_collidingEntities[i]->SetUserData((void*)ut::TRE4);
				}
			}
		}
		else
		{
			_ground->SummonTree((rand() % 4), _collision->GetCollisions().back()->_position, *_world);
			
			_ground->GetTrees().back()->CalculateMultiplier(_camera->GetSize(), _camera->GetPosition());
		}
		_collision->GetCollisions().pop_back();

	}

	_ground->Update();
	_score = 0;
	for (int i = 0; i < _ground->GetTrees().size(); i++)
	{
		_score += _ground->GetTrees()[i]->GetValue();
	}
	_score -= (_ground->GetTrees().size() * 10);

	_world->SetGravity(b2Vec2(0, GRAVITY));


	_scoreString = "Score: ";
	for (int i = 0; i < (6 - to_string(_score).size()); i++)
		_scoreString.append("0");

	_text->setString(_scoreString + to_string(_score));
	_text->setPosition(sf::Vector2f(_camera->GetPosition().x + (_camera->GetSize().x / 2) + SCOREOFFSET.x, _camera->GetPosition().y - (_camera->GetSize().y / 2) + SCOREOFFSET.y));
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

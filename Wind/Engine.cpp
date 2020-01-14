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

	if (Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		_camera->SetPosition(sf::Vector2f(_camera->GetPosition().x + 10, _camera->GetPosition().y));
	if (Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		_camera->SetPosition(sf::Vector2f(_camera->GetPosition().x - 10, _camera->GetPosition().y));

}

void Engine::RenderFrame()
{
	_window->clear(SKYCOLOR);

	_ground->Draw(_window);
	_cannon->Draw(_window);
	_wind->Draw(_window);
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

	_world->SetGravity(b2Vec2(0, GRAVITY));
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

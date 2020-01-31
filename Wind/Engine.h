#ifndef _ENGINE_H
#define _ENGINE_H

#include "CollisionHandler.h"
#include "Camera.h"
#include "Ground.h"
#include "Cannon.h"
#include "Wind.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define GRAVITY 1
#define SKYCOLOR sf::Color(16, 48, 64, 255)
#define SCOREOFFSET sf::Vector2f(-200.0f, 10.0f)

class Engine
{
private:
	SFMLDebugDraw* _debugDraw;

	CollisionHandler* _collision;
	sf::RenderWindow* _window;
	b2World* _world;
	Ground* _ground;
	Camera* _camera;
	Wind* _wind;
	Cannon* _cannon;

	sf::Font _font;
	sf::Text* _text;
	std::string _scoreString;
	int _score;

	sf::Vector2f _mousePos;

	bool Init();
	void MainLoop();
	void ProcessInput();
	void RenderFrame();
	void Update();
public:
	Engine() {};
	~Engine() {};

	void Go();
};

#endif
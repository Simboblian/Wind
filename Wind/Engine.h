#ifndef _ENGINE_H
#define _ENGINE_H

#include "Camera.h"
#include "Ground.h"
#include "Cannon.h"
#include "Wind.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define GRAVITY 1
#define SKYCOLOR sf::Color(16, 48, 64, 255)

class Engine
{
private:
	SFMLDebugDraw* _debugDraw;

	sf::RenderWindow* _window;
	b2World* _world;
	Ground* _ground;
	Camera* _camera;
	Wind* _wind;
	Cannon* _cannon;

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
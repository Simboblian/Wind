#ifndef CAMERA_H
#define CAMERA_H

#include "SFML\Graphics.hpp"

class Camera
{
private:
	sf::Vector2f position, vector, size, windowSize;

	bool fade = false;

	sf::View view;
	sf::RectangleShape viewWindow;
public:
	sf::View GetCamera() { return view; };
	sf::Vector2f GetPosition() { return position; };
	sf::Vector2f GetSize() { return size; };
	sf::RectangleShape GetViewWindow() { return viewWindow; };
	void SetZoom(float Zoom) { view.zoom(Zoom); };

	void Resize(sf::Vector2u NewSize);

	void ApplyVector(sf::Vector2f Vector) { vector += Vector; };
	void SetPosition(sf::Vector2f Position) { position = Position; };

	void Update(sf::RenderWindow& Window);

	Camera(sf::Vector2u Size);
	Camera();
	~Camera();
};

#endif
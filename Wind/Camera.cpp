#include "Camera.h"

void Camera::Resize(sf::Vector2u NewSize)
{
	sf::Vector2f sizePercentage;

	size = sf::Vector2f(NewSize.x/* * 0.25*/, NewSize.y/* * 0.25*/);
	view.reset(sf::FloatRect(0, 0, size.x, size.y));
}

void Camera::Update(sf::RenderWindow& Window)
{
	size = view.getSize();
	position += vector;
	view.setCenter(position);

	Window.setView(view);
}

Camera::Camera(sf::Vector2u Size)
{
	size = sf::Vector2f(Size.x, Size.y);
	position = sf::Vector2f(0, 0);
	view.reset(sf::FloatRect(0, 0, size.x, size.y));
	view.setCenter(sf::Vector2f(position));
}

Camera::Camera()
{
}


Camera::~Camera()
{
}

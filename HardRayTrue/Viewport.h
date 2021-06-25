#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Canvas.h"

class Viewport
{
	sf::Vector2f size;
	float distanceToCamera;

	Vector3f getPosFromCanvasPos(const Canvas &canvas, const sf::Vector2f &pos);

public:
	Viewport(sf::Vector2f size, float distanceToCamera): size {size}, distanceToCamera { distanceToCamera } {}
	~Viewport() {}
};

 
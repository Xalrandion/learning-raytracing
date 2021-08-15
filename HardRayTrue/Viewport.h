#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Canvas.h"

class Viewport
{
	sf::Vector2f size;
	double distanceToCamera;

public:
	Vector3d getPosFromCanvasPos(const Canvas& canvas, const sf::Vector2f& pos) const;
	Viewport(sf::Vector2f size, double distanceToCamera): size {size}, distanceToCamera { distanceToCamera } {}
	~Viewport() {}
};

 
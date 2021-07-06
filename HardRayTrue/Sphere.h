#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	float radius;
	sf::Color color;
	Sphere() : Object(), radius(0), color(0) {}
	Sphere(Vector3f pos, float radius, sf::Color color) : Object(pos), radius{ radius }, color{color} {}
};


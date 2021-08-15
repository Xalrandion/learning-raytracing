#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	double radius;
	sf::Color color;
	double specular;
	double reflectivness;
	Sphere() : Object(), radius(0), color(0), specular(0), reflectivness(0) {}
	Sphere(Vector3d pos, double radius, sf::Color color, double specular, double reflectivness) : Object(pos), radius{ radius }, color{ color }, specular{ specular }, reflectivness{ reflectivness } {}
};


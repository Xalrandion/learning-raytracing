#pragma once
#include <vector>
#include "Sphere.h"
#include "Light.h"


class Scene
{

public: 
	std::vector<Sphere> objects;
	std::vector<Light*> lights;
};


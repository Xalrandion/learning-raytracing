#pragma once
#include "Vector.h"
 
class Object
{

public:
	Object(): pos { Vector3f(0.0f, 0.0f, 0.0f)} {}
	Object(const Vector3f &pos): pos{pos} {}
	Vector3f getPos();
public:
	Vector3f pos;

};


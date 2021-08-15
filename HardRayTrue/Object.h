#pragma once
#include "Vector.h"
 
class Object
{

public:
	Object(): pos { Vector3d(0.0f, 0.0f, 0.0f)} {}
	Object(const Vector3d &pos): pos{pos} {}
	Vector3d getPos();
public:
	Vector3d pos;

};


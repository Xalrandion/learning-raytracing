#pragma once

class Vector3
{
public:
	Vector3(int _x, int _y, int _z) : x{ _x }, y{ _y }, z{ _z } {}
	Vector3() : Vector3(0, 0, 0) {}

	int x;
	int y;
	int z;
};

class Vector3f
{
public: 
	Vector3f(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z } {}
	Vector3f() : Vector3f(0, 0, 0) {}

	float x;
	float y;
	float z;
};
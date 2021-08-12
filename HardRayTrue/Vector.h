#pragma once

#include <Eigen/Dense>

class Vector3
{
public:
	Vector3(int _x, int _y, int _z) : x{ _x }, y{ _y }, z{ _z } {}
	Vector3() : Vector3(0, 0, 0) {}
	Eigen::Vector3i toEigen() const;

	int x;
	int y;
	int z;
};

class Vector3f
{

public: 
	static Vector3f fromEigen(Eigen::Vector3f v);
	Vector3f(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z } {}
	Vector3f() : Vector3f(0, 0, 0) {}
	Eigen::Vector3f toEigen() const;

	float x;
	float y;
	float z;
};
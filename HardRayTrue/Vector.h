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

class Vector3d
{

public: 
	static Vector3d fromEigen(Eigen::Vector3d v);
	Vector3d(double _x, double _y, double _z) : x{ _x }, y{ _y }, z{ _z } {}
	Vector3d() : Vector3d(0, 0, 0) {}
	Eigen::Vector3d toEigen() const;

	double x;
	double y;
	double z;
};
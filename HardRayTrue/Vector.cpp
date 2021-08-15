#include <Eigen/Dense>
#include "Vector.h"

Eigen::Vector3i Vector3::toEigen() const
{
	return Eigen::Vector3i(this->x, this->y, this->z);
}

Eigen::Vector3d Vector3d::toEigen() const
{
	return Eigen::Vector3d(this->x, this->y, this->z);
}

Vector3d Vector3d::fromEigen(Eigen::Vector3d v)
{
	return Vector3d(v.x(), v.y(), v.z());
}
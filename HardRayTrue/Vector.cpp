#include <Eigen/Dense>
#include "Vector.h"

Eigen::Vector3i Vector3::toEigen() const
{
	return Eigen::Vector3i(this->x, this->y, this->z);
}

Eigen::Vector3f Vector3f::toEigen() const
{
	return Eigen::Vector3f(this->x, this->y, this->z);
}
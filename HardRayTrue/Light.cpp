#include <math.h>  
#include "Light.h"
#include "Calculations.h"
#include "Constant.h"


double Light::computeSpecularIntensity(Vector3d rayDir, Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent) const
{
	if (specularExponent < 0) return 0;

	auto reflectionVector = reflectRay(rayDir, targetNormale).toEigen();
	auto r_dot_viewV = reflectionVector.dot(viewVector.toEigen());
	
	if (r_dot_viewV <= 0) return 0;

	auto s = reflectionVector.norm() * viewVector.toEigen().norm();
	auto p = pow(r_dot_viewV / s, specularExponent);
	return intensity * p;
}

double AmbiantLight::computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const
{
	return intensity;
}

double LigthWithDirection::calculateLightIntensityFromRayDirection(Vector3d rayDirection, Vector3d targetNormale) const
{
	auto rdir_dot_normale = targetNormale.toEigen().dot(rayDirection.toEigen());
	if (rdir_dot_normale <= 0) return 0;

	return intensity * rdir_dot_normale / (rayDirection.toEigen().norm() * targetNormale.toEigen().norm());
}

double PointLight::computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const {

	auto eigenRayDir = pos.toEigen() - targetPos.toEigen();
	auto shadowProducer = computeClosestInteraction(targetPos, Vector3d::fromEigen(eigenRayDir), objects, 0.001, 1);
	if (shadowProducer)
		return 0;
	auto i  = calculateLightIntensityFromRayDirection(Vector3d::fromEigen(eigenRayDir), targetNormale) + computeSpecularIntensity(Vector3d::fromEigen(eigenRayDir), targetPos, targetNormale, viewVector, specularExponent);
	return i;
}

double DirectionalLight::computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const {

	auto shadowProducer = computeClosestInteraction(targetPos, direction, objects, 0.001, RAY_MAX);
	if (shadowProducer)
		return 0;
	return calculateLightIntensityFromRayDirection(direction, targetNormale) + computeSpecularIntensity(direction, targetPos, targetNormale, viewVector, specularExponent);
}
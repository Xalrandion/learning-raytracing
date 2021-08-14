#include <math.h>  
#include "Light.h"
#include "Calculations.h"
#include "Constant.h"


float Light::computeSpecularIntensity(Vector3f rayDir, Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent) const
{
	if (specularExponent < 0) return 0;

	auto reflectionVector = reflectRay(rayDir, targetNormale).toEigen();
	auto r_dot_viewV = reflectionVector.dot(viewVector.toEigen());
	
	if (r_dot_viewV <= 0) return 0;

	auto s = reflectionVector.norm() * viewVector.toEigen().norm();
	auto p = pow(r_dot_viewV / s, specularExponent);
	return intensity * p;
}

float AmbiantLight::computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const
{
	return intensity;
}

float LigthWithDirection::calculateLightIntensityFromRayDirection(Vector3f rayDirection, Vector3f targetNormale) const
{
	auto rdir_dot_normale = targetNormale.toEigen().dot(rayDirection.toEigen());
	if (rdir_dot_normale <= 0) return 0;

	return intensity * rdir_dot_normale / (rayDirection.toEigen().norm() * targetNormale.toEigen().norm());
}

float PointLight::computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const {

	auto eigenRayDir = pos.toEigen() - targetPos.toEigen();
	auto shadowProducer = computeClosestInteraction(targetPos, Vector3f::fromEigen(eigenRayDir), objects, 0.001, 1);
	if (shadowProducer)
		return 0;
	auto i  = calculateLightIntensityFromRayDirection(Vector3f::fromEigen(eigenRayDir), targetNormale) + computeSpecularIntensity(Vector3f::fromEigen(eigenRayDir), targetPos, targetNormale, viewVector, specularExponent);
	return i;
}

float DirectionalLight::computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const {

	auto shadowProducer = computeClosestInteraction(targetPos, direction, objects, 0.001, RAY_MAX);
	if (shadowProducer)
		return 0;
	return calculateLightIntensityFromRayDirection(direction, targetNormale) + computeSpecularIntensity(direction, targetPos, targetNormale, viewVector, specularExponent);
}
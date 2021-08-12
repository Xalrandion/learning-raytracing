#pragma once
#include "Vector.h"
#include "Sphere.h"

class Light
{
protected:
	float computeSpecularIntensity(Vector3f rayDir, Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent) const;
public:
	virtual float computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere> &objects) const = 0;
	float intensity;

	Light(float i): intensity {i} {}
	Light() : Light (0) {}
	virtual ~Light() = 0 {};
};

class AmbiantLight : public Light {

public:
	AmbiantLight(float intensity): Light(intensity) {}
	float computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const;
	~AmbiantLight() {};
};

class LigthWithDirection : public Light {

protected:
	LigthWithDirection(float i): Light(i) {}
	float calculateLightIntensityFromRayDirection(Vector3f rayDirection, Vector3f targetNormale) const;
public:
	virtual ~LigthWithDirection() = 0 {};
};

class PointLight : public LigthWithDirection {

public:
	Vector3f pos;
	PointLight(Vector3f pos, float intensity) : LigthWithDirection(intensity),  pos{ pos } {}
	float computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const;
	~PointLight() {}
};

class DirectionalLight : public LigthWithDirection {

public:
	Vector3f direction;
	DirectionalLight(Vector3f direction, float intensity) : LigthWithDirection(intensity), direction{ direction } {}
	float computeLightIntensity(Vector3f targetPos, Vector3f targetNormale, Vector3f viewVector, float specularExponent, const std::vector<Sphere>& objects) const;
	~DirectionalLight() {}
};
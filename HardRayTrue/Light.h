#pragma once
#include "Vector.h"
#include "Sphere.h"

class Light
{
protected:
	double computeSpecularIntensity(Vector3d rayDir, Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent) const;
public:
	virtual double computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere> &objects) const = 0;
	double intensity;

	Light(double i): intensity {i} {}
	Light() : Light (0) {}
	virtual ~Light() = 0 {};
};

class AmbiantLight : public Light {

public:
	AmbiantLight(double intensity): Light(intensity) {}
	double computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const;
	~AmbiantLight() {};
};

class LigthWithDirection : public Light {

protected:
	LigthWithDirection(double i): Light(i) {}
	double calculateLightIntensityFromRayDirection(Vector3d rayDirection, Vector3d targetNormale) const;
public:
	virtual ~LigthWithDirection() = 0 {};
};

class PointLight : public LigthWithDirection {

public:
	Vector3d pos;
	PointLight(Vector3d pos, double intensity) : LigthWithDirection(intensity),  pos{ pos } {}
	double computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const;
	~PointLight() {}
};

class DirectionalLight : public LigthWithDirection {

public:
	Vector3d direction;
	DirectionalLight(Vector3d direction, double intensity) : LigthWithDirection(intensity), direction{ direction } {}
	double computeLightIntensity(Vector3d targetPos, Vector3d targetNormale, Vector3d viewVector, double specularExponent, const std::vector<Sphere>& objects) const;
	~DirectionalLight() {}
};
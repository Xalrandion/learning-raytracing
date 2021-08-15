#pragma once

#include <memory>
#include "Sphere.h"
#include "Scene.h"

std::unique_ptr<std::pair<Sphere, double>> computeClosestInteraction(const Vector3d& origin, const Vector3d& viewportPos,  const std::vector<Sphere>& objects, double rayMinSize, double rayMaxSize);
Vector3d reflectRay(Vector3d ray, Vector3d reflectBase);
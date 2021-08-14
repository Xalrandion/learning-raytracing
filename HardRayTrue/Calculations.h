#pragma once

#include <memory>
#include "Sphere.h"
#include "Scene.h"

std::unique_ptr<std::pair<Sphere, float>> computeClosestInteraction(const Vector3f& origin, const Vector3f& viewportPos,  const std::vector<Sphere>& objects, float rayMinSize, float rayMaxSize);
Vector3f reflectRay(Vector3f ray, Vector3f reflectBase);
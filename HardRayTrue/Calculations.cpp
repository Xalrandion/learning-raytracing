#include "Calculations.h"
#include "Constant.h"

std::pair<float, float> intersectSphere(const Vector3f& origin, const Vector3f& viewportPos, const Sphere& sphere) {

    Eigen::Vector3f co = origin.toEigen() - sphere.pos.toEigen();
    // ax² + bx + c  

    float  a = viewportPos.toEigen().dot(viewportPos.toEigen());
    float b = 2 * (co.dot(viewportPos.toEigen()));
    float c = co.dot(co) - (sphere.radius * sphere.radius);

    // b² - 4ac
    float delta = (b * b) - (4 * a * c);
    if (delta < 0) return std::pair<float, float>(RAY_MAX, RAY_MAX);

    // solutions
    return std::pair<float, float>((-b + sqrt(delta)) / (2 * a), (-b - sqrt(delta)) / (2 * a));
}

bool isBeetween(float x, float min, float max) {
    return x >= min && x <= max;
}

std::unique_ptr<std::pair<Sphere, float>> computeClosestInteraction(const Vector3f& origin, const Vector3f& viewportPos, const std::vector<Sphere>& objects, float rayMinSize, float rayMaxSize) {

    float rayClosestCollistion = rayMaxSize;
    Sphere closestSphere;
    auto isSphereFound = false;

    for (auto it = objects.begin(); it != objects.end(); ++it) {

        auto intersections = intersectSphere(origin, viewportPos, *it);
        if (isBeetween(intersections.first, rayMinSize, rayMaxSize) && intersections.first < rayClosestCollistion) {
            rayClosestCollistion = intersections.first;
            closestSphere = *it;
            isSphereFound = true;
        }
        if (isBeetween(intersections.second, rayMinSize, rayMaxSize) && intersections.second < rayClosestCollistion) {
            rayClosestCollistion = intersections.second;
            closestSphere = *it;
            isSphereFound = true;
        }

    }

    if (!isSphereFound) return std::unique_ptr< std::pair<Sphere, float>>(nullptr);
    return std::make_unique<std::pair<Sphere, float>>(std::pair<Sphere, float>(closestSphere, rayClosestCollistion));
}
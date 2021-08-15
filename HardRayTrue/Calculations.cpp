#include "Calculations.h"
#include "Constant.h"

Vector3d reflectRay(Vector3d ray, Vector3d reflectBase) {

    auto eiRay = ray.toEigen();
    auto eiReflectBase = reflectBase.toEigen();
    return Vector3d::fromEigen((2.0f * eiReflectBase * eiRay.dot(eiReflectBase)) - eiRay);
}

std::pair<double, double> intersectSphere(const Vector3d& origin, const Vector3d& viewportPos, const Sphere& sphere) {

    Eigen::Vector3d co = origin.toEigen() - sphere.pos.toEigen();
    // ax² + bx + c  

    double  a = viewportPos.toEigen().dot(viewportPos.toEigen());
    double b = 2 * (co.dot(viewportPos.toEigen()));
    double c = co.dot(co) - (sphere.radius * sphere.radius);

    // b² - 4ac
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return std::pair<double, double>(RAY_MAX, RAY_MAX);

    // solutions
    return std::pair<double, double>((-b + sqrt(delta)) / (2 * a), (-b - sqrt(delta)) / (2 * a));
}

bool isBeetween(double x, double min, double max) {
    return x >= min && x <= max;
}

std::unique_ptr<std::pair<Sphere, double>> computeClosestInteraction(const Vector3d& origin, const Vector3d& viewportPos, const std::vector<Sphere>& objects, double rayMinSize, double rayMaxSize) {

    double rayClosestCollistion = rayMaxSize;
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

    if (!isSphereFound) return std::unique_ptr< std::pair<Sphere, double>>(nullptr);
    return std::make_unique<std::pair<Sphere, double>>(std::pair<Sphere, double>(closestSphere, rayClosestCollistion));
}
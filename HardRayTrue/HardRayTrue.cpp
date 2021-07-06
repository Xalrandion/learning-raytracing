// HardRayTrue.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include "includes/Canvas.h"
#include "Viewport.h"
#include "Scene.h"

constexpr auto RAY_MAX = 2000000000;
constexpr auto RAY_MIN = -2000000000;

sf::Color BG_COLOR = sf::Color::White;

void drawCanvas(sf::RenderWindow& target, const Canvas &canvas) {

    auto tex = canvas.getTexture();
    target.draw(sf::Sprite(tex));
}

sf::VideoMode getScreenPercentageMode(float percent) {

    auto fullDesktopMode = sf::VideoMode::getDesktopMode();
    auto width = (percent * fullDesktopMode.width) / 100;
    auto height = (percent * fullDesktopMode.height) / 100;
    return sf::VideoMode(height, height);
}

std::pair<float, float> intersectSphere(const Vector3f& origin, const Vector3f& viewportPos, const Sphere& sphere) {

    Eigen::Vector3f co = origin.toEigen() - sphere.pos.toEigen();
    // ax² + bx + c  

    auto a = viewportPos.toEigen().dot(viewportPos.toEigen());
    auto b = 2 * (co.dot(viewportPos.toEigen()));
    auto c = co.dot(co) - (sphere.radius * sphere.radius);

    // b² - 4ac
    auto delta = (b * b) - (4 * a * c);
    if (delta < 0) return std::pair<float, float>(RAY_MAX, RAY_MAX);

    // solutions
    return std::pair<float, float>(((b * -1) + (sqrt(delta)) / (2 * a)), ((b * -1) - (sqrt(delta)) / (2 * a)));
}

bool isBeetween(float x, float min, float max) {
    return x >= min && x <= max;
}

sf::Color traceRay(const Vector3f& origin, const Vector3f& viewportPos, const Scene &scene, int rayMinSize, int rayMaxSize) {

    auto rayClosestCollistion = rayMaxSize;
    Sphere closestSphere;
    auto isSphereFound = false;

    for (auto it = scene.objects.begin(); it != scene.objects.end(); ++it) {

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
    if (!isSphereFound) return BG_COLOR;
    return closestSphere.color;
}

void drawScene(Canvas &canvas, const Viewport &viewport, const Vector3f &origin, const Scene &scene) {

    auto currentCanvasPos = sf::Vector2f(0, 0); 
    currentCanvasPos.x = ((float)canvas.getSize().x / 2) * -1;
    auto s2 = currentCanvasPos.x < canvas.getSize().x / 2;
    for (currentCanvasPos.x = ((float)canvas.getSize().x / 2) * -1; currentCanvasPos.x < canvas.getSize().x / 2; currentCanvasPos.x++) {
        for (currentCanvasPos.y = ((float)canvas.getSize().y / 2) * -1; currentCanvasPos.y < canvas.getSize().y / 2; currentCanvasPos.y++) {

            auto viewportPos = viewport.getPosFromCanvasPos(canvas, currentCanvasPos);
            auto color = traceRay(origin, viewportPos, scene, 1, RAY_MAX);
            canvas.putPixel(currentCanvasPos, color); 
        }
    }
}

int main()
{

    sf::RenderWindow window(getScreenPercentageMode(65), "Some hardcore rays if you ask me");
    
    Canvas canvas(window.getSize().x, window.getSize().y);

    Viewport viewport(sf::Vector2f(1, 1), 1);
    Vector3f origin(0, 0, 0);
    Scene scene; 

    scene.objects.push_back(Sphere(Vector3f(0, -1, 3), 1, sf::Color::Red));
    scene.objects.push_back(Sphere(Vector3f(2, 0, 4), 1, sf::Color::Blue));
    scene.objects.push_back(Sphere(Vector3f(-2, 0, 4), 1, sf::Color::Cyan));
   

    canvas.clear();
    drawScene(canvas, viewport, origin, scene); 
    std::cout << "render done" << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawCanvas(window, canvas);
        window.display();
    }

    return 0;
}
// HardRayTrue.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include "includes/Canvas.h"
#include "Viewport.h"
#include "Scene.h"
#include "Constant.h"
#include "Calculations.h"

sf::Color BG_COLOR = sf::Color::Black;

void drawCanvas(sf::RenderWindow& target, const Canvas &canvas) {

    auto tex = canvas.getTexture();
    target.draw(sf::Sprite(tex));
}

sf::VideoMode getScreenPercentageMode(double percent) {

    auto fullDesktopMode = sf::VideoMode::getDesktopMode();
    auto width = (percent * fullDesktopMode.width) / 100;
    auto height = (percent * fullDesktopMode.height) / 100;
    return sf::VideoMode(height, height);
}


double computeLightning(Scene scene, const Vector3d &targetPos, const Vector3d &tagetNormale, const Vector3d &viewVector, double specularExponent) {

    double intensity = 0;
    for (auto it = scene.lights.begin(); it != scene.lights.end(); ++it) {
        auto i = (*it)->computeLightIntensity(targetPos, tagetNormale, viewVector, specularExponent, scene.objects);
        intensity += i;
    }
    return intensity;
}

sf::Uint8 clampColorComponent(double colorComponent) {
    return floor(colorComponent < 0 ? 0 : colorComponent > 255 ? 255 : colorComponent);
}

sf::Color generateClampedColor(double r, double g, double b) {

    return sf::Color(clampColorComponent(r), clampColorComponent(g), clampColorComponent(b));
}

Eigen::Vector3i col;

sf::Color traceRay(const Vector3d& origin, const Vector3d& viewportPos, const Scene &scene, double rayMinSize, double rayMaxSize, int depth) {


    auto closestInteraction = computeClosestInteraction(origin, viewportPos, scene.objects, rayMinSize, rayMaxSize);
    if (!closestInteraction) return BG_COLOR;

    auto rayClosestCollistion = closestInteraction->second;
    auto closestSphere = closestInteraction->first;

    auto eiViewportPos = viewportPos.toEigen();
    auto eiClosestSphereIntersesctPos = origin.toEigen() + ((double)rayClosestCollistion * eiViewportPos);
    auto eiClosestSphereNormaleAtPos = eiClosestSphereIntersesctPos - closestSphere.pos.toEigen();
    auto eiClosestSphereNormaleAtPosNormalized =  eiClosestSphereNormaleAtPos / eiClosestSphereNormaleAtPos.norm();

    
    sf::Color baseColor(closestSphere.color);
    
    auto intensity = computeLightning(scene, Vector3d::fromEigen(eiClosestSphereIntersesctPos), Vector3d::fromEigen(eiClosestSphereNormaleAtPosNormalized), Vector3d::fromEigen(eiViewportPos * -1), closestSphere.specular);
    sf::Color localColor = generateClampedColor((double)baseColor.r * intensity, (double)baseColor.g * intensity, (double)baseColor.b * intensity);

    if (closestSphere.reflectivness <= 0 || depth <= 0) return localColor;
   
    auto reflectedColor = traceRay(Vector3d::fromEigen(eiClosestSphereIntersesctPos),
        reflectRay(Vector3d::fromEigen(eiViewportPos * -1), Vector3d::fromEigen(eiClosestSphereNormaleAtPosNormalized)),
        scene,
        0.001, 
        RAY_MAX, 
        depth - 1);
    auto r = ((double)localColor.r * (1.0f - closestSphere.reflectivness)) + ((double)reflectedColor.r * closestSphere.reflectivness);
    auto g = ((double)localColor.g * (1.0f - closestSphere.reflectivness)) + ((double)reflectedColor.g * closestSphere.reflectivness);
    auto b = ((double)localColor.b * (1.0f - closestSphere.reflectivness)) + ((double)reflectedColor.b * closestSphere.reflectivness);
    
    auto clamped = generateClampedColor(r, g, b);
    return clamped; 
}

void drawScene(Canvas &canvas, const Viewport &viewport, const Vector3d &origin, const Scene &scene) {

    auto currentCanvasPos = sf::Vector2f(0, 0); 
    for (currentCanvasPos.x = ((double)canvas.getSize().x / 2) * -1; currentCanvasPos.x < canvas.getSize().x / 2; currentCanvasPos.x++) {
        for (currentCanvasPos.y = ((double)canvas.getSize().y / 2) * -1; currentCanvasPos.y < canvas.getSize().y / 2; currentCanvasPos.y++) {

            auto viewportPos = viewport.getPosFromCanvasPos(canvas, currentCanvasPos);
            auto color = traceRay(origin, viewportPos, scene, 1, RAY_MAX, 5);
            canvas.putPixel(currentCanvasPos, color); 
            //std::cout << "Pixex [" << currentCanvasPos.x << "; " << currentCanvasPos.y << "] drawn." << std::endl;
        }
    }
}

int main()
{

    sf::RenderWindow window(getScreenPercentageMode(50), "Some hardcore rays if you ask me");
    
    Canvas canvas(window.getSize().x, window.getSize().y);

    Viewport viewport(sf::Vector2f(1, 1), 1);
    Vector3d origin(0, 0, 0);
    Scene scene; 

    scene.objects.push_back(Sphere(Vector3d(0, -1, 3), 1, sf::Color::Red, 500, 0.2));
    scene.objects.push_back(Sphere(Vector3d(2, 0, 4), 1, sf::Color::Blue, 500, 0.3));
    scene.objects.push_back(Sphere(Vector3d(-2, 0, 4), 1, sf::Color::Green, 10, 0.4));
    scene.objects.push_back(Sphere(Vector3d(0, -5001, 0), 5000, sf::Color::Magenta, 1000, 0.5));
    scene.lights.push_back(new AmbiantLight(0.2));
    scene.lights.push_back(new PointLight(Vector3d(2, 1, 0), 0.6));
    scene.lights.push_back(new DirectionalLight(Vector3d(1, 4, 4), 0.2));
   

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
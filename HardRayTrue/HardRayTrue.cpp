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


float computeLightning(Scene scene, const Vector3f &targetPos, const Vector3f &tagetNormale, const Vector3f &viewVector, float specularExponent) {

    float intensity = 0;
    for (auto it = scene.lights.begin(); it != scene.lights.end(); ++it) {
        auto i = (*it)->computeLightIntensity(targetPos, tagetNormale, viewVector, specularExponent, scene.objects);
        intensity += i;
    }
    return intensity;
}

sf::Color traceRay(const Vector3f& origin, const Vector3f& viewportPos, const Scene &scene, int rayMinSize, int rayMaxSize) {


    auto closestInteraction = computeClosestInteraction(origin, viewportPos, scene.objects, rayMinSize, rayMaxSize);
    if (!closestInteraction) return BG_COLOR;

    auto rayClosestCollistion = closestInteraction->second;
    auto closestSphere = closestInteraction->first;

    auto eiViewportPos = viewportPos.toEigen();
    auto eiClosestSphereIntersesctPos = origin.toEigen() + ((float)rayClosestCollistion * eiViewportPos);
    auto eiClosestSphereNormaleAtPos = eiClosestSphereIntersesctPos - closestSphere.pos.toEigen();
    auto eiClosestSphereNormaleAtPosNormalized =  eiClosestSphereNormaleAtPos / eiClosestSphereNormaleAtPos.norm();

    
    sf::Color color(closestSphere.color);
    
    auto intensity = computeLightning(scene, Vector3f::fromEigen(eiClosestSphereIntersesctPos), Vector3f::fromEigen(eiClosestSphereNormaleAtPosNormalized), Vector3f::fromEigen(eiViewportPos * -1), closestSphere.specular);



    float r = (float)color.r * intensity;
    float g = (float)color.g * intensity;
    float b = (float)color.b * intensity;

    // std::cout << "intensity: " << intensity << " r: " << r << " g: " << g << " b: " << b << std::endl;
    

    r = r > 0 ? r : 0;
    g = g > 0 ? g : 0;
    b = b > 0 ? b : 0;
    color.r = r > 255 ? 255 : r;
    color.g = g > 255 ? 255 : g;
    color.b = b > 255 ? 255 : b;

    return color;
}

void drawScene(Canvas &canvas, const Viewport &viewport, const Vector3f &origin, const Scene &scene) {

    auto currentCanvasPos = sf::Vector2f(0, 0); 
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

    sf::RenderWindow window(getScreenPercentageMode(60), "Some hardcore rays if you ask me");
    
    Canvas canvas(window.getSize().x, window.getSize().y);

    Viewport viewport(sf::Vector2f(1, 1), 1);
    Vector3f origin(0, 0, 0);
    Scene scene; 

    scene.objects.push_back(Sphere(Vector3f(0, -1, 3), 1, sf::Color::Red, 500));
    scene.objects.push_back(Sphere(Vector3f(2, 0, 4), 1, sf::Color::Blue, 500));
    scene.objects.push_back(Sphere(Vector3f(-2, 0, 4), 1, sf::Color::Green, 10));
    scene.objects.push_back(Sphere(Vector3f(0, -5001, 0), 5000, sf::Color::Yellow, 1000));
    scene.lights.push_back(new AmbiantLight(0.2));
    scene.lights.push_back(new PointLight(Vector3f(2, 1, 0), 0.6));
    scene.lights.push_back(new DirectionalLight(Vector3f(1, 4, 4), 0.2));
   

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
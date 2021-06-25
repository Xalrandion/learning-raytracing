// HardRayTrue.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include "includes/Canvas.h"
#include "Viewport.h"


void drawCanvas(sf::RenderWindow& target, const Canvas &canvas) {

    auto tex = canvas.getTexture();
    target.draw(sf::Sprite(tex));
}

sf::VideoMode getScreenPercentageMode(float percent) {

    auto fullDesktopMode = sf::VideoMode::getDesktopMode();
    auto width = (percent * fullDesktopMode.width) / 100;
    auto height = (percent * fullDesktopMode.height) / 100;
    return sf::VideoMode(width, height);
}


int main()
{

    sf::RenderWindow window(getScreenPercentageMode(65), "Some hardcore rays if you ask me");
    
    Canvas canvas(window.getSize().x, window.getSize().y);
    Viewport viewport(sf::Vector2f(50, 50), 1);
    Vector3 origin(0, 0, 0);
   

    canvas.clear();
    canvas.putPixel(sf::Vector2f(0, 0), sf::Color::Red);
    
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
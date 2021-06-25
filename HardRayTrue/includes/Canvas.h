#pragma once

#include "../Vector.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

class Canvas
{
private: 

	sf::RenderTexture texture;
	sf::Vector2u textureSize;
	
	sf::Vector2f translateToTexturePosition(const sf::Vector2f& position);
	bool validateTexturePosition(const sf::Vector2f &pos); 

public:

	void putPixel(const sf::Vector2f &position, const sf::Color &color) ;
	const sf::Vector2u getSize() const;
	void clear();
	sf::Texture getTexture() const;
	Canvas(int width, int height);
	~Canvas();
};

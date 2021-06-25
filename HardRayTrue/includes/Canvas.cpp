#include "Canvas.h"

void Canvas::putPixel(const sf::Vector2f &position, const sf::Color &color)
{

	auto texturePos = translateToTexturePosition(position); 
	if (!validateTexturePosition(texturePos)) return;

	auto vertexArray = sf::VertexArray(sf::Points);
	vertexArray.append(sf::Vertex(texturePos, color));
	texture.draw(vertexArray);
}

void Canvas::clear()
{
	this->texture.clear();
}

sf::Texture Canvas::getTexture() const
{
	return this->texture.getTexture();
}

Canvas::Canvas(int width, int height)
{
	if (!this->texture.create(width, height)) {
		throw "Cannot create canvas";
	}
	textureSize = this->texture.getSize();
}

Canvas::~Canvas() { }

sf::Vector2f Canvas::translateToTexturePosition(const sf::Vector2f& position)
{
	return sf::Vector2f((textureSize.x / 2) + position.x, (textureSize.y / 2) - position.y);
}
		
bool Canvas::validateTexturePosition(const sf::Vector2f& pos)
{
	return pos.x <= textureSize.x && pos.y <= textureSize.y;
}

const sf::Vector2u Canvas::getSize() const {
	return textureSize;
}
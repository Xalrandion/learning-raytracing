#include "Viewport.h"


Vector3f Viewport::getPosFromCanvasPos(const Canvas& canvas, const sf::Vector2f &pos) const
{
	float x = pos.x * size.x / canvas.getSize().x; 
	float y = pos.y * size.y / canvas.getSize().y;
	float z = distanceToCamera; 


 	return Vector3f(x, y, z);
}

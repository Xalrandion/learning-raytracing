#include "Viewport.h"


Vector3d Viewport::getPosFromCanvasPos(const Canvas& canvas, const sf::Vector2f &pos) const
{
	double x = (pos.x * size.x) / canvas.getSize().x; 
	double y = (pos.y * size.y) / canvas.getSize().y;
	double z = distanceToCamera; 


 	return Vector3d(x, y, z);
}

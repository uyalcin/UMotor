#ifndef __CUBE_H
#define __CUBE_H

#include "Entity.h"
#include "Vector3.h"
#include "Plane.h"

class Cube : public Entity
{
	public:
		Cube(float size, Vector3);
		Cube();
		~Cube();
		
		std::vector<Plane*> planes;

		void draw(sf::RenderWindow& window) override;
		void rotate(float angleX, float angleY);
};

#endif

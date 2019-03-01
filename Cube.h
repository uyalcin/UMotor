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
		std::vector<Plane*> getPlanes() override;
		void rotate(float angleX, float angleY);
		void initPos(Vector3 v);
		void translate(Vector3 v);
		void scale(Vector3 s);
		bool isSelected(sf::Vector2f);
		void applyRotation();
};

#endif

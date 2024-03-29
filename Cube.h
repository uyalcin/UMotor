#ifndef __CUBE_H
#define __CUBE_H

#include "Entity.h"
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Primitive.h"

class Cube : public Entity
{
	public:
		Cube(float size, Vector3);
		Cube();
		~Cube();
		

		void draw(sf::RenderWindow& window) override;
		std::vector<Primitive*> getPrimitives() override;

		void rotate(float angleX, float angleY) override;
		void initPos(Vector3 v) override;
		void translate(Vector3 v) override;
		void scale(Vector3 s) override;
		bool isSelected(sf::Vector2f) override;
};

#endif

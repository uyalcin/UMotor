#ifndef __OBJECT_H
#define __OBJECT_H

#include "Entity.h"
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Primitive.h"
#include <string>

class Object : public Entity
{
	public:
		Object(float size, Vector3);
		Object();
		Object(const char* path, Vector3 pos, float scale);
		~Object();
		

		void draw(sf::RenderWindow& window) override;
		std::vector<Primitive*> getPrimitives() override;

		void rotate(float angleX, float angleY) override;
		void initPos(Vector3 v) override;
		void translate(Vector3 v) override;
		void scale(Vector3 s) override;
		bool isSelected(sf::Vector2f) override;
};

#endif

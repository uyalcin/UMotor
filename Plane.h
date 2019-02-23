#ifndef __PLANE_H
#define __PLANE_H

#include "Entity.h"
#include "Vector3.h"
#include <vector>

class Plane : public Entity
{
	public:
		Plane();
		Plane(Vector3 position, float size);
		Plane(Vector3, Vector3, Vector3, Vector3);
		~Plane();
		
		Vector3 a;
		Vector3 b;
		Vector3 c;
		Vector3 d;
		float size;
		float alpha;

		void rotate(float angle);
		void draw(sf::RenderWindow& window) override;
		std::vector<sf::Vertex> sorted_vertices;
		std::vector<Vector3> getVertex();
		void rotAroundZ(float angle);
		void rotAroundY(float angle);
		//std::vector<sf::Vertex> vertices;
};

#endif

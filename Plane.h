#ifndef __PLANE_H
#define __PLANE_H

#include "Entity.h"
#include "Vector3.h"
#include <vector>

class Matrix;

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

		// Texturing
		bool hasTexture = false;
		sf::Texture texture;
		void setTexture(sf::Texture tex);
		
		// Translation
		void translate(Vector3 v);

		// Rotation
		void backToZero();
		void backToLast();
		void rotAroundX(float angle);
		void rotAroundY(float angle);
		void rotAroundZ(float angle);

		//Scale
		void scale(Vector3 s);
		//std::vector<sf::Vertex> vertices;

		// Is Selected
		bool isSelected(sf::Vector2f mousePos);
};

#endif

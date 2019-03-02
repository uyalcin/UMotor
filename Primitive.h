#ifndef __PRIMITIVE_H
#define __PRIMITIVE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vector4.h"

class Primitive
{
	public:
		Primitive() {}
		~Primitive() {}

		virtual void draw(sf::RenderWindow& window) = 0;
		virtual std::vector<Vector4> getMvpVertex() = 0;

		virtual void rotate(float angle) = 0;

		// Translation
		virtual void initPos(Vector3 v) = 0;
		virtual void translate(Vector3 v) = 0;

		// Rotation
		virtual void rotAroundX(float angle) = 0;
		virtual void rotAroundY(float angle) = 0;
		virtual void rotAroundZ(float angle) = 0;

		//Scale
		virtual void scale(Vector3 s) = 0;

		// Is Selected
		virtual bool isSelected(sf::Vector2f mousePos) = 0;
		
		bool isWireFrame = false;
		bool isPerspective = false;
};

#endif

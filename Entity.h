#ifndef __ENTITY_H
#define __ENTITY_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"
#include <vector>
#include "Primitive.h"

class Plane;

class Entity
{
	public:
		Entity();
		~Entity();

		std::vector<Primitive*> primitives;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual std::vector<Primitive*> getPrimitives() = 0;

		virtual void rotate(float angleX, float angleY) = 0;
		virtual void initPos(Vector3 v) = 0;
		virtual void translate(Vector3 v) = 0;
		virtual void scale(Vector3 s) = 0;
		virtual bool isSelected(sf::Vector2f) = 0;

		Vector3 position;
		Vector3 rotation;
		void setWireFrame(bool isWireFrame)
		{
			for(int i = 0; i < primitives.size(); i++)
			{
				primitives[i]->isWireFrame = isWireFrame;
			}
		}
		void setPerspective(bool isPerspective)
		{
			for(int i = 0; i < primitives.size(); i++)
			{
				primitives[i]->isPerspective = isPerspective;
			}
		}
};

#endif

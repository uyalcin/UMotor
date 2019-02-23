#ifndef __ENTITY_H
#define __ENTITY_H

#include <SFML/Graphics.hpp>
#include "Vector3.h"

class Entity
{
	public:
		Entity();
		~Entity();

		virtual void draw(sf::RenderWindow& window) = 0;

		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
};

#endif

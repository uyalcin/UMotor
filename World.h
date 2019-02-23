#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <memory>

#ifndef __WORLD_H
#define __WORLD_H


class World
{
	public:
		World();
		~World();

		void draw(sf::RenderWindow& window);
		void addEntity(std::shared_ptr<Entity> e);
	private:
		std::vector<std::shared_ptr<Entity>> world;
		int getSize();
		std::shared_ptr<Entity> getEntity(const int index);
};

#endif

#ifndef __WORLD_H
#define __WORLD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class World
{
	public:
		World();
		~World();

		void draw(sf::RenderWindow& window);
		void addEntity(std::shared_ptr<Entity> e);
		void setCamera(std::shared_ptr<Entity> cam);
		int getSize();
		std::shared_ptr<Entity> getEntity(const int index);
		void rotateCamera(float angleX, float angleY);
		void setWireFrame(bool isWireFrame);
		void setPerspective(bool isPerspective);
	private:
		std::vector<std::shared_ptr<Entity>> world;
		std::shared_ptr<Entity> camera;
};

#endif

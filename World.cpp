#include "World.h"

World::World()
{
}

World::~World()
{
	
}

void World::addEntity(std::shared_ptr<Entity> e)
{
	if(e != nullptr)
		world.push_back(e);
}

int World::getSize()
{
	return world.size();
}

std::shared_ptr<Entity> World::getEntity(const int index)
{
	return world[index];
}

void World::draw(sf::RenderWindow& window)
{
	for(int i = getSize(); --i >= 0;)
	{
		world[i]->draw(window);
	}
}

void World::setCamera(std::shared_ptr<Entity> cam)
{
	camera = cam;
}

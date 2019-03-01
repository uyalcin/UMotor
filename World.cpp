#include "World.h"
#include "Plane.h"

World::World()
{
}

World::~World()
{
	
}

bool comparePlaneDepth(Plane* plane1, Plane* plane2)
{
	std::vector<Vector4> mvpPosition1 = plane1->getMvpVertex();
	std::vector<Vector4> mvpPosition2 = plane2->getMvpVertex();

	/*float min1 = std::numeric_limits<float>::infinity();
	for(int i = 0; i < mvpPosition1.size(); i++)
		min1 = std::min((double)min1, sqrt(pow(mvpPosition1[i].x, 2) -  pow(mvpPosition1[i].z, 2)));

	float min2 = std::numeric_limits<float>::infinity();
	for(int i = 0; i < mvpPosition2.size(); i++)
		min2 = std::min((double)min2, sqrt(pow(mvpPosition2[i].x, 2) -  pow(mvpPosition2[i].z, 2)));*/

	float min1 = std::min(mvpPosition1[0].z, mvpPosition1[1].z);
	min1 = std::min(min1, mvpPosition1[2].z);
	min1 = std::min(min1, mvpPosition1[3].z);

	float min2 = std::min(mvpPosition2[0].z, mvpPosition2[1].z);
	min2 = std::min(min2, mvpPosition2[2].z);
	min2 = std::min(min2, mvpPosition2[3].z);

	return min1 < min2;

	/*float min1 = std::min(plane1->a.z, plane1->b.z);
	min1 = std::min(min1, plane1->c.z);
	min1 = std::min(min1, plane1->d.z);

	float min2 = std::min(plane2->a.z, plane2->b.z);
	min2 = std::min(min2, plane2->c.z);
	min2 = std::min(min2, plane2->d.z);
	return min1 < min2;*/
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
	std::vector<Plane*> allPlanes;
	
	for(int i = getSize(); --i >= 0;)
	{
		std::vector<Plane*> planes = world[i]->getPlanes();
		for(int j = planes.size(); --j >= 0;)
			allPlanes.push_back(planes[j]);
	}
	std::sort(allPlanes.begin(), allPlanes.end(), comparePlaneDepth);
	for(int i = 0; i < allPlanes.size(); i++)
		allPlanes[i]->draw(window);
}

void World::setCamera(std::shared_ptr<Entity> cam)
{
	camera = cam;
}

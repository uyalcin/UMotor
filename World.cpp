#include "World.h"
#include "Primitive.h"

World::World()
{
}

World::~World()
{
	
}

bool comparePlaneDepth(Primitive* plane1, Primitive* plane2)
{
	std::vector<Vector4> mvpPosition1 = plane1->getMvpVertex();
	std::vector<Vector4> mvpPosition2 = plane2->getMvpVertex();

	float min1 = std::numeric_limits<float>::infinity();
	for(int i = 0; i < mvpPosition1.size(); i++)
		min1 = std::min(min1, mvpPosition1[i].z);

	float min2 = std::numeric_limits<float>::infinity();
	for(int i = 0; i < mvpPosition2.size(); i++)
		min2 = std::min(min2, mvpPosition2[i].z);

	/*float min1 = std::min(mvpPosition1[0].z, mvpPosition1[1].z);
	min1 = std::min(min1, mvpPosition1[2].z);
	min1 = std::min(min1, mvpPosition1[3].z);

	float min2 = std::min(mvpPosition2[0].z, mvpPosition2[1].z);
	min2 = std::min(min2, mvpPosition2[2].z);
	min2 = std::min(min2, mvpPosition2[3].z);*/

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
	std::vector<Primitive*> allPlanes;
	
	for(int i = getSize(); --i >= 0;)
	{
		std::vector<Primitive*> primitives = world[i]->getPrimitives();
		for(int j = primitives.size(); --j >= 0;)
			allPlanes.push_back(primitives[j]);
	}
	//std::sort(allPlanes.begin(), allPlanes.end(), comparePlaneDepth);
	for(int i = 0; i < allPlanes.size(); i++)
		allPlanes[i]->draw(window);
}

void World::setCamera(std::shared_ptr<Entity> cam)
{
	camera = cam;
}

void World::rotateCamera(float angleX, float angleY)
{
	for(int i = getSize(); --i >= 0;)
	{
		world[i]->rotate(angleX, angleY);
	}
}

void World::setWireFrame(bool isWireFrame)
{
	for(int i = getSize(); --i >= 0;)
	{
		world[i]->setWireFrame(isWireFrame);
	}	
}

void World::setPerspective(bool isPerspective)
{
	for(int i = getSize(); --i >= 0;)
	{
		world[i]->setPerspective(isPerspective);
	}
}

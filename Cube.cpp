#include "Cube.h"
#include <algorithm>
#include "header.h"
#include <math.h>

bool compareVertexDepth(const Vector3 vertex1, const Vector3 vertex2)
{
	return vertex1.z < vertex2.z;
}

Cube::Cube(float _size, Vector3 pos)
{
	float size = _size;
	Vector3 a(-size, size, size);
	Vector3 b(size, size, size);
	Vector3 c(size, -size, size);
	Vector3 d(-size, -size, size);
	Vector3 e(-size, size, -size);
	Vector3 f(size, size, -size);
	Vector3 g(size, -size, -size);
	Vector3 h(-size, -size, -size);

	Vector3 i = a + Vector3(0, 0, 1);
	Vector3 j = b + Vector3(0, 0, 1);
	Vector3 k = c + Vector3(0, 0, 1);

	primitives.push_back(new Plane(a, b, c, d));
	primitives.push_back(new Plane(b, f, g, c));
	primitives.push_back(new Plane(a, e, h, d));
	primitives.push_back(new Plane(e, f, g, h));
	primitives.push_back(new Plane(a, e, f, b));
	primitives.push_back(new Plane(d, c, g, h));

	//primitives.push_back(new Triangle(i, j, k));
	//planes[0]->isDebug = true;

	initPos(pos);
}

Cube::Cube():
	Cube(0.5, Vector3(0, 0, 0))
{

}
Cube::~Cube()
{

}

void Cube::draw(sf::RenderWindow& window)
{
	/*std::sort(primitives.begin(), primitives.end(), comparePlaneDepth);
	for(int i = 0; i < primitives.size(); i++)
		primitives[i]->draw(window);*/
}

std::vector<Primitive*> Cube::getPrimitives()
{
	return primitives;
}

void Cube::rotate(float angleX, float angleY)
{
	if(angleY <= -PI)
		angleY = PI;
	if(angleY >= PI)
		angleY = PI;
	if(angleX <= -PI)
		angleX = PI;
	if(angleX >= PI)
		angleX = PI;

	// Check the angles limits
	if(!(angleX >= -PI && angleX <= PI && angleY >= -PI && angleY <= PI))
		return;

	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->rotAroundX((-angleX * PI) / 180.0f);
		primitives[i]->rotAroundY((angleY * PI) / 180.0f);
		//planes[i]->rotAroundZ((angleY * PI) / 180.0f);
	}
}

void Cube::initPos(Vector3 v)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->initPos(v);
	}
}
void Cube::translate(Vector3 v)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->translate(v);
	}
}

void Cube::scale(Vector3 s)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->scale(s);
	}
}

bool Cube::isSelected(sf::Vector2f mousePos)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		if(primitives[i]->isSelected(mousePos))
			return true;
	}
	return false;
}

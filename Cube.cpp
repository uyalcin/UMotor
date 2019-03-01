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

	planes.push_back(new Plane(a, b, c, d));
	planes.push_back(new Plane(b, f, g, c));
	planes.push_back(new Plane(a, e, h, d));
	planes.push_back(new Plane(e, f, g, h));
	planes.push_back(new Plane(a, e, f, b));
	planes.push_back(new Plane(d, c, g, h));
	planes[0]->isDebug = true;

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
	/*std::sort(planes.begin(), planes.end(), comparePlaneDepth);
	for(int i = 0; i < planes.size(); i++)
		planes[i]->draw(window);*/
}

std::vector<Plane*> Cube::getPlanes()
{
	return planes;
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

	for(int i = 0; i < planes.size(); i++)
	{
		planes[i]->rotAroundX((-angleX * PI) / 180.0f);
		planes[i]->rotAroundY((angleY * PI) / 180.0f);
		//planes[i]->rotAroundZ((angleY * PI) / 180.0f);
	}
}

void Cube::initPos(Vector3 v)
{
	for(int i = 0; i < planes.size(); i++)
	{
		planes[i]->initPos(v);
	}
}
void Cube::translate(Vector3 v)
{
	for(int i = 0; i < planes.size(); i++)
	{
		planes[i]->translate(v);
	}
}

void Cube::scale(Vector3 s)
{
	for(int i = 0; i < planes.size(); i++)
	{
		planes[i]->scale(s);
	}
}

bool Cube::isSelected(sf::Vector2f mousePos)
{
	for(int i = 0; i < planes.size(); i++)
	{
		if(planes[i]->isSelected(mousePos))
			return true;
	}
	return false;
}

void Cube::applyRotation()
{
	for(int i = 0; i < planes.size(); i++)
	{
		planes[i]->applyRotation();
	}
}

#include "Cube.h"
#include <algorithm>
#include "header.h"
#include <math.h>

bool comparePlaneDepth(Plane* plane1, Plane* plane2)
{
	std::vector<Vector4> mvpPosition1 = plane1->getMvpVertex();
	std::vector<Vector4> mvpPosition2 = plane2->getMvpVertex();

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
	std::sort(planes.begin(), planes.end(), comparePlaneDepth);
	for(int i = 0; i < planes.size(); i++)
		planes[i]->draw(window);
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

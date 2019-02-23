#include "Cube.h"
#include <algorithm>
#include "header.h"

bool comparePlaneDepth(const Plane* plane1, const Plane* plane2)
{
	float max1 = std::max(plane1->a.z, plane1->b.z);
	max1 = std::max(max1, plane1->c.z);
	max1 = std::max(max1, plane1->d.z);
	float max2 = std::max(plane2->a.z, plane2->b.z);
	max2 = std::max(max2, plane2->c.z);
	max2 = std::max(max2, plane2->d.z);
	return max1 < max2;
}

bool compareVertexDepth(const Vector3 vertex1, const Vector3 vertex2)
{
	return vertex1.z < vertex2.z;
}

Cube::Cube(float _size, Vector3 pos = Vector3(0, 0, 0))
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
	a = a + pos;
	b = b + pos;
	c = c + pos;
	d = d + pos;
	e = e + pos;
	f = f + pos;
	g = g + pos;
	h = h + pos;

	planes.push_back(new Plane(a, b, c, d));
	planes.push_back(new Plane(b, f, g, c));
	planes.push_back(new Plane(a, e, h, d));
	planes.push_back(new Plane(e, f, g, h));
	planes.push_back(new Plane(a, e, f, b));
	planes.push_back(new Plane(d, c, g, h));
}

Cube::Cube():
	Cube(0.5)
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
	}
}

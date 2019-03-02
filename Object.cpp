#include "Object.h"
#include <algorithm>
#include "header.h"
#include <math.h>
#include "Triangle.h"
#include <sstream>
#include <fstream>

void load_obj(const char* filename, std::vector<sf::Vector3f>& vertices, std::vector<std::vector<int>>& faces) {

	std::ifstream in(filename, std::ios::in);
	if (!in) { std::cerr << "Cannot open " << filename << std::endl; exit(1); }
	std::string line;
	while (getline(in, line)) 
	{
		if (line.substr(0, 2) == "v ") { // vertex data
			std::istringstream s(line.substr(2));
			sf::Vector3f v; 
			s >> v.x; 
			s >> v.y;
			s >> v.z;
			v.y = - v.y;
			//v.x = v.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
			//v.y = SCREEN_Y - SCREEN_Y * (v.y + 1) / 2.0f;
			vertices.push_back(v);
		} 
		else if (line.substr(0, 2) == "f ") { // vertex data
			std::istringstream lines(line.substr(2));
			std::string s;
			std::vector<int> fv;
			int j = 0;

			for (int i = 0; i < 3; i++)
			{
				lines >> s;
				std::stringstream test(s);
				std::string segment;
				std::vector<std::string> seglist;
				while(std::getline(test, segment, '/'))
				{
					if(j%3==0)
						fv.push_back(std::atoi(segment.c_str())-1);
					j++;
				}
			}
			faces.push_back(fv);
		}
	}
	
}

Object::Object(const char* path, Vector3 pos, float _scale)
{
	// Load obj
	std::vector<sf::Vector3f> vertex;
	std::vector<std::vector<int>> faces;
	load_obj(path, vertex, faces);

	for(int i = 0; i < faces.size(); i++)
	{
		/*for(int j = 0; j < 3; j++)
		{
			if(faces[i][j] < vertex.size() && faces[i][j] >= 0)
			{
				//sf::Color randomColor(0, 0, rand()%(255 - 100) + 100);
				//sf::Color randomColor(rand()%255, rand()%255, rand()%255);
				//vertices.push_back(sf::Vertex(sf::Vector2f(vertex[faces[i][j]].x, vertex[faces[i][j]].y), randomColor));
				sf::Vector3f v = vertex[faces[i][j]];
				primitives.push_back(new Triangle(
			}
		}*/
		Vector3 a(vertex[faces[i][0]].x, vertex[faces[i][0]].y, vertex[faces[i][0]].z);
		Vector3 b(vertex[faces[i][1]].x, vertex[faces[i][1]].y, vertex[faces[i][1]].z);
		Vector3 c(vertex[faces[i][2]].x, vertex[faces[i][2]].y, vertex[faces[i][2]].z);
		primitives.push_back(new Triangle(a, b, c));
	}
	initPos(pos);
	scale(Vector3(_scale, _scale, _scale));
}

Object::Object(float _size, Vector3 pos)
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

Object::Object():
	Object(0.5, Vector3(0, 0, 0))
{

}
Object::~Object()
{

}

void Object::draw(sf::RenderWindow& window)
{
	/*std::sort(primitives.begin(), primitives.end(), comparePlaneDepth);
	for(int i = 0; i < primitives.size(); i++)
		primitives[i]->draw(window);*/
}

std::vector<Primitive*> Object::getPrimitives()
{
	return primitives;
}

void Object::rotate(float angleX, float angleY)
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

void Object::initPos(Vector3 v)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->initPos(v);
	}
}
void Object::translate(Vector3 v)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->translate(v);
	}
}

void Object::scale(Vector3 s)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		primitives[i]->scale(s);
	}
}

bool Object::isSelected(sf::Vector2f mousePos)
{
	for(int i = 0; i < primitives.size(); i++)
	{
		if(primitives[i]->isSelected(mousePos))
			return true;
	}
	return false;
}

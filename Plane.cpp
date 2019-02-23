#include "Plane.h"
#include "header.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>

Plane::Plane()
{

}

bool compareFaces(const std::vector<int> & f1, const std::vector<int> & f2)
{
	int mini1, mini2;
	mini1 = std::min(f1[0], f1[1]);
	mini1 = std::min(mini1, f1[2]);
	mini2 = std::min(f2[0], f2[1]);
	mini2 = std::min(mini2, f2[2]);
	return mini1 > mini2;
}

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
			v.x = v.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
			v.y = SCREEN_Y - SCREEN_Y * (v.y + 1) / 2.0f;
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

Plane::Plane(Vector3 _position, float _size)
{
	position = _position;
	size = _size;
	a = position;
	b = position;
	c = position;
	d = position;

	a.x -= size / 2.0f;
	a.y -= size / 2.0f;
	b.x += size / 2.0f;
	b.y -= size / 2.0f;
	c.x += size / 2.0f;
	c.y += size / 2.0f;
	d.x -= size / 2.0f;
	d.y += size / 2.0f;

	a.z = 0.5f;
	b.z = 0.5f;
	c.z = 0.5f;
	d.z = 0.5f;
	alpha = 0.0f;

	// Load obj
	/*std::vector<sf::Vector3f> vertex;
	std::vector<std::vector<int>> faces;
	load_obj("suzanne.obj", vertex, faces);
	
	std::sort(faces.begin(), faces.end(), compareFaces);

	for(int i = 0; i < faces.size(); i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(faces[i][j] < vertex.size() && faces[i][j] >= 0)
			{
				//sf::Color randomColor(0, 0, rand()%(255 - 100) + 100);
				sf::Color randomColor(rand()%255, rand()%255, rand()%255);
				vertices.push_back(sf::Vertex(sf::Vector2f(vertex[faces[i][j]].x, vertex[faces[i][j]].y), randomColor));
			}
		}
	}*/
}

Plane::~Plane()
{
}

Plane::Plane(Vector3 a, Vector3 b, Vector3 c, Vector3 d):
	a(a),
	b(b),
	c(c),
	d(d)
{
	size = abs(a.x - b.x);

	alpha = 0.0f;
}

void Plane::rotAroundZ(float angle)
{
	Vector3 _a, _b, _c, _d;
	_a=a;
	_b=b;
	_c=c;
	_d=d;

	// Rotation around Z
	_a.x = (cos(angle)*a.x - sin(angle)*a.z);
	_d.x = (cos(angle)*d.x - sin(angle)*d.z);
	_b.x = (cos(angle)*b.x - sin(angle)*b.z);
	_c.x = (cos(angle)*c.x - sin(angle)*c.z);

	_a.z = (sin(angle)*a.x + cos(angle)*a.z);
	_d.z = (sin(angle)*d.x + cos(angle)*d.z);
	_b.z = (sin(angle)*b.x + cos(angle)*b.z);
	_c.z = (sin(angle)*c.x + cos(angle)*c.z);

	a=_a;
	b=_b;
	c=_c;
	d=_d;
}

void Plane::rotAroundY(float angle)
{
	Vector3 _a, _b, _c, _d;
	_a=a;
	_b=b;
	_c=c;
	_d=d;

	// Rotation around Y
	_a.z = (cos(angle)*a.z - sin(angle)*a.y);
	_d.z = (cos(angle)*d.z - sin(angle)*d.y);
	_b.z = (cos(angle)*b.z - sin(angle)*b.y);
	_c.z = (cos(angle)*c.z - sin(angle)*c.y);

	_a.y = (sin(angle)*a.z + cos(angle)*a.y);
	_d.y = (sin(angle)*d.z + cos(angle)*d.y);
	_b.y = (sin(angle)*b.z + cos(angle)*b.y);
	_c.y = (sin(angle)*c.z + cos(angle)*c.y);

	a=_a;
	b=_b;
	c=_c;
	d=_d;
}

void Plane::rotate(float angle)
{
	float distance = size / 2.0f;
	
	rotAroundZ(angle);
	rotAroundY(angle);
}

void Plane::draw(sf::RenderWindow& window)
{
	alpha = (0.1f * PI) / 180.0f;
	//rotate(alpha);

	std::vector<sf::Vertex> vertices;
	float _ax = a.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
	float _ay = SCREEN_Y * (a.y + 1) / 2.0f;
	float _bx = b.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
	float _by = SCREEN_Y * (b.y + 1) / 2.0f;
	float _cx = c.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
	float _cy = SCREEN_Y * (c.y + 1) / 2.0f;
	float _dx = d.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f);
	float _dy = SCREEN_Y * (d.y + 1) / 2.0f;
	
	vertices.push_back(sf::Vertex(sf::Vector2f(_ax, _ay), sf::Color::Red));
	vertices.push_back(sf::Vertex(sf::Vector2f(_bx, _by), sf::Color::Green));
	vertices.push_back(sf::Vertex(sf::Vector2f(_cx, _cy), sf::Color::Blue));
	vertices.push_back(sf::Vertex(sf::Vector2f(_dx, _dy), sf::Color::Yellow));


	window.draw(&vertices[0], vertices.size(), sf::Quads);
	// window.draw(&vertices[0], vertices.size(), sf::Triansles);
		//std::cout << positions[i].x;
	//}	
	//std::cout << vertices.size() << std::endl;
	/*for(int i = 0; i < SCREEN_X; i++)
		for(int j = 0; j < SCREEN_Y; j++)
		{
			vertices.push_back(sf::Vertex(sf::Vector2f(i, j), sf::Color::Red));
		}*/
	
	
}

std::vector<Vector3> Plane::getVertex()
{
	std::vector<Vector3> vertex;
	vertex.push_back(a);
	vertex.push_back(b);
	vertex.push_back(c);
	vertex.push_back(d);
	return vertex;
}

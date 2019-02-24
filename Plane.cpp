#include "Plane.h"
#include "header.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Matrix.h"

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
	hasTexture = false;

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
	hasTexture = false;
	alpha = 0.0f;
}

void Plane::backToZero()
{
	a = a - position;
	b = b - position;
	c = c - position;
	d = d - position;
}

void Plane::backToLast()
{
	a = a + position;
	b = b + position;
	c = c + position;
	d = d + position;
}

void Plane::rotAroundX(float angle)
{

	// Rotation Matrix Rx
	Matrix Rx(Vector3(1, 0, 0),
		  Vector3(0, cos(angle), -sin(angle)),
		  Vector3(0, sin(angle), cos(angle)));

	backToZero();

	// Rotation around X
	a = a * Rx;
	b = b * Rx;
	c = c * Rx;
	d = d * Rx;

	backToLast();
}

void Plane::rotAroundY(float angle)
{
	// Rotation Matrix Ry
	Matrix Ry(Vector3(cos(angle), 0, sin(angle)),
		  Vector3(0, 1, 0),
		  Vector3(-sin(angle), 0, cos(angle)));

	backToZero();

	// Rotation around Y
	a = a * Ry;
	b = b * Ry;
	c = c * Ry;
	d = d * Ry;

	backToLast();
}

void Plane::rotAroundZ(float angle)
{
	// Rotation Matrix Rz
	Matrix Rz(Vector3(cos(angle), -sin(angle), 0),
		  Vector3(sin(angle), cos(angle), 0),
		  Vector3(0, 0, 1));

	backToZero();

	// Rotation around Z
	a = a * Rz;
	b = b * Rz;
	c = c * Rz;
	d = d * Rz;

	backToLast();
}

void Plane::rotate(float angle)
{
	float distance = size / 2.0f;
	
	rotAroundX(angle);
	rotAroundY(angle);
}

void Plane::scale(Vector3 s)
{
	backToZero();
	a = a * s;
	b = b * s;
	c = c * s;
	d = d * s;
	backToLast();
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

	sf::VertexArray quad(sf::Quads, 4);
	if(hasTexture)
	{
		quad[0] = sf::Vertex(sf::Vector2f(_ax, _ay));
		quad[1] = sf::Vertex(sf::Vector2f(_bx, _by));
		quad[2] = sf::Vertex(sf::Vector2f(_cx, _cy));
		quad[3] = sf::Vertex(sf::Vector2f(_dx, _dy));

		const float sizeTex = 1024.f;
		quad[0].texCoords = sf::Vector2f(0.f, 0.f);
		quad[1].texCoords = sf::Vector2f(sizeTex, 0.f);
		quad[2].texCoords = sf::Vector2f(sizeTex, sizeTex);
		quad[3].texCoords = sf::Vector2f(0.f, sizeTex);

		window.draw(quad, &texture);
	}
	else
	{
		quad[0] = sf::Vertex(sf::Vector2f(_ax, _ay), sf::Color::Red);
		quad[1] = sf::Vertex(sf::Vector2f(_bx, _by), sf::Color::Green);
		quad[2] = sf::Vertex(sf::Vector2f(_cx, _cy), sf::Color::Blue);
		quad[3] = sf::Vertex(sf::Vector2f(_dx, _dy), sf::Color::Yellow);

		window.draw(quad);
	}
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

void Plane::setTexture(sf::Texture tex)
{
	texture = tex;
	hasTexture = true;
}

void Plane::translate(Vector3 v)
{
	position = position + v;
	a = a + v;
	b = b + v;
	c = c + v;
	d = d + v;
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

bool Plane::isSelected(sf::Vector2f mousePos)
{
	// Screen to world positions
	float mx = (mousePos.x - SCREEN_X/2.0f) / (SCREEN_Y / 2.0f);
	float my = ((2.0f * mousePos.y) / SCREEN_Y) - 1.0f;

	// Get the AABB of the plane
	float minX;
	float minY;
	float maxX;
	float maxY;

	minX = std::min(a[0], b[0]);
	minX = std::min(minX, c[0]);
	minX = std::min(minX, d[0]);

	minY = std::min(a[1], b[1]);
	minY = std::min(minY, c[1]);
	minY = std::min(minY, d[1]);

	maxX = std::max(a[0], b[0]);
	maxX = std::max(maxX, c[0]);
	maxX = std::max(maxX, d[0]);

	maxY = std::max(a[1], b[1]);
	maxY = std::max(maxY, c[1]);
	maxY = std::max(maxY, d[1]);

	return (mx >= minX && mx <= maxX && my >= minY && my <= maxY);
}

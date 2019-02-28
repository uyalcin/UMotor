#include "Plane.h"
#include "header.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Matrix.h"
#include "Matrix4.h"
#include "Vector4.h"

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

	a.z = 0.0f;
	b.z = 0.0f;
	c.z = 0.0f;
	d.z = 0.0f;
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
	Matrix4 Rx(Vector4(1, 0, 0, 0),
		   Vector4(0, cos(angle), sin(angle), 0),
		   Vector4(0, -sin(angle), cos(angle), 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();

	// Rotation around X
	/*a = a * Rx;
	b = b * Rx;
	c = c * Rx;
	d = d * Rx;*/
	ViewRotationPitchMatrix = ViewRotationPitchMatrix * Rx;

	//backToLast();
}

void Plane::rotAroundY(float angle)
{
	Matrix4 Ry(Vector4(cos(angle), 0, -sin(angle), 0),
		   Vector4(0, 1, 0, 0),
		   Vector4(sin(angle), 0, cos(angle), 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();
	// Rotation around Y
	/*a = a * Ry;
	b = b * Ry;
	c = c * Ry;
	d = d * Ry;*/
	ViewRotationYawMatrix = ViewRotationYawMatrix * Ry;

	//backToLast();
}

void Plane::rotAroundZ(float angle)
{
	// Rotation Matrix Rz
	Matrix4 Rz(Vector4(cos(angle), sin(angle), 0, 0),
		   Vector4(-sin(angle), cos(angle), 0, 0),
		   Vector4(0, 0, 1, 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();

	// Rotation around Z
	/*a = a * Rz;
	b = b * Rz;
	c = c * Rz;
	d = d * Rz;*/
	//modelMatrix = modelMatrix * Rz;

	//backToLast();
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

	Matrix4 sM(Vector4(s.x,   0,   0,   0),
		   Vector4(  0, s.y,   0,   0),
		   Vector4(  0,   0, s.z,   0),
		   Vector4(  0,   0,   0,   1));

	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);
	Vector4 _d(d, 1);

	a = sM * _a;
	b = sM * _b;
	c = sM * _c;
	d = sM * _d;

	backToLast();
}

std::vector<Vector4> Plane::getMvpVertex()
{
	// View Matrix
	Matrix4 ViewMatrix = ViewTranslationMatrix * ViewRotationPitchMatrix * ViewRotationYawMatrix * ViewScaleMatrix;

	// ModelMatrix
	Matrix4 ModelMatrix = ModelTranslationMatrix * ModelRotationMatrix * ModelScaleMatrix;

	// MVP Matrix
	Matrix4 MVP = ViewMatrix * ModelMatrix;

	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);
	Vector4 _d(d, 1);

	Vector4 ma = MVP * _a;
	Vector4 mb = MVP * _b;
	Vector4 mc = MVP * _c;
	Vector4 md = MVP * _d;

	std::vector<Vector4> mvp_Vertex;

	mvp_Vertex.push_back(ma);
	mvp_Vertex.push_back(mb);
	mvp_Vertex.push_back(mc);
	mvp_Vertex.push_back(md);

	return mvp_Vertex;
}

void Plane::draw(sf::RenderWindow& window)
{
	std::vector<Vector4> mvpVertex = getMvpVertex();

	Vector4 ma = mvpVertex[0];
	Vector4 mb = mvpVertex[1];
	Vector4 mc = mvpVertex[2];
	Vector4 md = mvpVertex[3];

	if(ma.z >= 0 || mb.z >= 0 || mc.z >= 0 || md.z >= 0)
		return;

	alpha = (0.1f * PI) / 180.0f;
	//rotate(alpha);

	std::vector<sf::Vertex> vertices;
	
	/*float _ax = (a.x * a.z * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _ay = (SCREEN_Y * (a.y * a.z + 1) / 2.0f);
	float _bx = (b.x * b.z * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _by = (SCREEN_Y * (b.y * b.z + 1) / 2.0f);
	float _cx = (c.x * c.z * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _cy = (SCREEN_Y * (c.y * c.z + 1) / 2.0f);
	float _dx = (d.x * d.z * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _dy = (SCREEN_Y * (d.y * d.z + 1) / 2.0f);*/

	float _ax = (ma.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _ay = (SCREEN_Y * (ma.y + 1) / 2.0f);
	float _bx = (mb.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _by = (SCREEN_Y * (mb.y + 1) / 2.0f);
	float _cx = (mc.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _cy = (SCREEN_Y * (mc.y + 1) / 2.0f);
	float _dx = (md.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	float _dy = (SCREEN_Y * (md.y + 1) / 2.0f);

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

void Plane::initPos(Vector3 v)
{
	Matrix4 t(Vector4(1, 0, 0, v.x),
		  Vector4(0, 1, 0, v.y),
		  Vector4(0, 0, 1, v.z),
		  Vector4(0, 0, 0, 1));

	Vector4 _position(position, 1);
	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);
	Vector4 _d(d, 1);

	//position = t * _position;
	/*a = t * _a;
	b = t * _b;
	c = t * _c;
	d = t * _d;*/
	ModelTranslationMatrix = ModelTranslationMatrix * t;
}

void Plane::translate(Vector3 v)
{
	Matrix4 t(Vector4(1, 0, 0, v.x),
		  Vector4(0, 1, 0, v.y),
		  Vector4(0, 0, 1, v.z),
		  Vector4(0, 0, 0, 1));

	Vector4 _position(position, 1);
	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);
	Vector4 _d(d, 1);

	position = t * _position;
	a = t * _a;
	b = t * _b;
	c = t * _c;
	d = t * _d;
	//translationMatrix = t * translationMatrix;
	//ViewTranslationMatrix = ViewTranslationMatrix * t;
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

void Plane::applyRotation()
{
	/*Vector4 _a(a, 1);
	a = modelMatrix * _a;
Vector4 _b(b, 1);
	b = modelMatrix * _b;
Vector4 _c(c, 1);
	c = modelMatrix * _c;
Vector4 _d(d, 1);
	d = modelMatrix * _d;*/
	/*modelMatrix.v1 = Vector4(1, 0, 0, 0);
	modelMatrix.v2 = Vector4(0, 1, 0, 0);
	modelMatrix.v3 = Vector4(0, 0, 1, 0);
	modelMatrix.v4 = Vector4(0, 0, 0, 1);*/
}

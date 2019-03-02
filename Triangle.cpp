#include "Triangle.h"
#include "header.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Matrix.h"
#include "Matrix4.h"
#include "Vector4.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Vector3 _position, float _size)
{
	position = _position;
	size = _size;
	a = position;
	b = position;
	c = position;

	a.x -= size / 2.0f;
	a.y -= size / 2.0f;
	b.x += size / 2.0f;
	b.y -= size / 2.0f;
	c.x += size / 2.0f;
	c.y += size / 2.0f;

	a.z = 0.0f;
	b.z = 0.0f;
	c.z = 0.0f;
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

Triangle::~Triangle()
{
}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c):
	a(a),
	b(b),
	c(c)
{
	size = abs(a.x - b.x);
	hasTexture = false;
	alpha = 0.0f;
}

void Triangle::backToZero()
{
	a = a - position;
	b = b - position;
	c = c - position;
}

void Triangle::backToLast()
{
	a = a + position;
	b = b + position;
	c = c + position;
}

void Triangle::rotAroundX(float angle)
{
	// Rotation Matrix Rx
	Matrix4 Rx(Vector4(1, 0, 0, 0),
		   Vector4(0, cos(angle), sin(angle), 0),
		   Vector4(0, -sin(angle), cos(angle), 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();

	ViewRotationPitchMatrix = ViewRotationPitchMatrix * Rx;

	//backToLast();
}

void Triangle::rotAroundY(float angle)
{
	Matrix4 Ry(Vector4(cos(angle), 0, -sin(angle), 0),
		   Vector4(0, 1, 0, 0),
		   Vector4(sin(angle), 0, cos(angle), 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();

	ViewRotationYawMatrix = ViewRotationYawMatrix * Ry;

	//backToLast();
}

void Triangle::rotAroundZ(float angle)
{
	// Rotation Matrix Rz
	Matrix4 Rz(Vector4(cos(angle), sin(angle), 0, 0),
		   Vector4(-sin(angle), cos(angle), 0, 0),
		   Vector4(0, 0, 1, 0),
		   Vector4(0, 0, 0, 1));

	//backToZero();

	//modelMatrix = modelMatrix * Rz;

	//backToLast();
}

void Triangle::rotate(float angle)
{
	float distance = size / 2.0f;
	
	rotAroundX(angle);
	rotAroundY(angle);
}

void Triangle::scale(Vector3 s)
{
	backToZero();

	Matrix4 sM(Vector4(s.x,   0,   0,   0),
		   Vector4(  0, s.y,   0,   0),
		   Vector4(  0,   0, s.z,   0),
		   Vector4(  0,   0,   0,   1));

	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);

	a = sM * _a;
	b = sM * _b;
	c = sM * _c;

	backToLast();
}

std::vector<Vector4> Triangle::getMvpVertex()
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

	Vector4 ma = MVP * _a;
	Vector4 mb = MVP * _b;
	Vector4 mc = MVP * _c;

	const float factor = 2.0f;
	if(isPerspective)
	{
		ma = ma * (factor/(-ma.z));
		mb = mb * (factor/(-mb.z));
		mc = mc * (factor/(-mc.z));
	}

	std::vector<Vector4> mvp_Vertex;

	mvp_Vertex.push_back(ma);
	mvp_Vertex.push_back(mb);
	mvp_Vertex.push_back(mc);

	return mvp_Vertex;
}

void Triangle::draw(sf::RenderWindow& window)
{
	std::vector<Vector4> mvpVertex = getMvpVertex();

	Vector4 ma = mvpVertex[0];
	Vector4 mb = mvpVertex[1];
	Vector4 mc = mvpVertex[2];

	if(ma.z >= 0 || mb.z >= 0 || mc.z >= 0)
		return;

	alpha = (0.1f * PI) / 180.0f;
	//rotate(alpha);

	std::vector<sf::Vertex> vertices;

	float _ax;
	float _ay;
	float _bx;
	float _by;
	float _cx;
	float _cy;
	
	_ax = (ma.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	_ay = (SCREEN_Y * (ma.y + 1) / 2.0f);
	_bx = (mb.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	_by = (SCREEN_Y * (mb.y + 1) / 2.0f);
	_cx = (mc.x * (SCREEN_Y / 2.0f) + (SCREEN_X / 2.0f));
	_cy = (SCREEN_Y * (mc.y + 1) / 2.0f);

	sf::VertexArray quad;
	if(!isWireFrame)
		quad = sf::VertexArray(sf::Triangles, 3);
	else
		quad = sf::VertexArray(sf::Lines, 3);
	//sf::VertexArray quad(sf::Lines, 3);
	if(hasTexture)
	{
		quad[0] = sf::Vertex(sf::Vector2f(_ax, _ay));
		quad[1] = sf::Vertex(sf::Vector2f(_bx, _by));
		quad[2] = sf::Vertex(sf::Vector2f(_cx, _cy));

		const float sizeTex = 1024.f;
		quad[0].texCoords = sf::Vector2f(0.f, 0.f);
		quad[1].texCoords = sf::Vector2f(sizeTex, 0.f);
		quad[2].texCoords = sf::Vector2f(sizeTex, sizeTex);

		window.draw(quad, &texture);
	}
	else
	{
		quad[0] = sf::Vertex(sf::Vector2f(_ax, _ay), sf::Color::Red);
		quad[1] = sf::Vertex(sf::Vector2f(_bx, _by), sf::Color::Green);
		quad[2] = sf::Vertex(sf::Vector2f(_cx, _cy), sf::Color::Blue);

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

void Triangle::setTexture(sf::Texture tex)
{
	texture = tex;
	hasTexture = true;
}

void Triangle::initPos(Vector3 v)
{
	Matrix4 t(Vector4(1, 0, 0, v.x),
		  Vector4(0, 1, 0, v.y),
		  Vector4(0, 0, 1, v.z),
		  Vector4(0, 0, 0, 1));

	Vector4 _position(position, 1);
	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);

	position = t * _position;
	a = t * _a;
	b = t * _b;
	c = t * _c;
	//ModelTranslationMatrix = ModelTranslationMatrix * t;
}

void Triangle::translate(Vector3 v)
{
	Matrix4 t(Vector4(1, 0, 0, v.x),
		  Vector4(0, 1, 0, v.y),
		  Vector4(0, 0, 1, v.z),
		  Vector4(0, 0, 0, 1));

	Vector4 _position(position, 1);
	Vector4 _a(a, 1);
	Vector4 _b(b, 1);
	Vector4 _c(c, 1);

	position = t * _position;
	a = t * _a;
	b = t * _b;
	c = t * _c;
	//translationMatrix = t * translationMatrix;
	//ViewTranslationMatrix = ViewTranslationMatrix * t;
}


bool Triangle::isSelected(sf::Vector2f mousePos)
{
	// Screen to world positions
	float mx = (mousePos.x - SCREEN_X/2.0f) / (SCREEN_Y / 2.0f);
	float my = ((2.0f * mousePos.y) / SCREEN_Y) - 1.0f;

	// Get the AABB of the plane
	float minX;
	float minY;
	float maxX;
	float maxY;

	std::vector<Vector4> mvp_Vertex = getMvpVertex();

	minX = std::min(mvp_Vertex[0][0], mvp_Vertex[1][0]);
	minX = std::min(minX, mvp_Vertex[2][0]);

	minY = std::min(mvp_Vertex[0][1], mvp_Vertex[1][1]);
	minY = std::min(minY, mvp_Vertex[2][1]);

	maxX = std::max(mvp_Vertex[0][0], mvp_Vertex[1][0]);
	maxX = std::max(maxX, mvp_Vertex[2][0]);

	maxY = std::max(mvp_Vertex[0][1], mvp_Vertex[1][1]);
	maxY = std::max(maxY, mvp_Vertex[2][1]);

	return (mx >= minX && mx <= maxX && my >= minY && my <= maxY);
}

#ifndef __PLANE_H
#define __PLANE_H

#include "Entity.h"
#include "Vector3.h"
#include <vector>
#include "Matrix4.h"
#include "Primitive.h"

class Matrix;

class Plane : public Primitive
{
	public:
		Plane();
		Plane(Vector3 position, float size);
		Plane(Vector3, Vector3, Vector3, Vector3);
		~Plane();
		
		Vector3 a;
		Vector3 b;
		Vector3 c;
		Vector3 d;
		float size;
		float alpha;

		void rotate(float angle)override;
		void draw(sf::RenderWindow& window) override;

		// Texturing
		bool hasTexture = false;
		sf::Texture texture;
		void setTexture(sf::Texture tex);

		Vector3 position;
		// Translation
		void initPos(Vector3 v)override;
		void translate(Vector3 v)override;

		// Rotation
		void backToZero();
		void backToLast();
		void rotAroundX(float angle)override;
		void rotAroundY(float angle)override;
		void rotAroundZ(float angle)override;

		//Scale
		void scale(Vector3 s)override;
		//std::vector<sf::Vertex> vertices;

		// Is Selected
		bool isSelected(sf::Vector2f mousePos)override;

		// Model Matrix
		Matrix4 ModelTranslationMatrix;
		Matrix4 ModelRotationMatrix;
		Matrix4 ModelScaleMatrix;

		// View Matrix
		Matrix4 ViewTranslationMatrix;
		Matrix4 ViewRotationPitchMatrix;
		Matrix4 ViewRotationYawMatrix;
		Matrix4 ViewScaleMatrix;

		std::vector<Vector4> getMvpVertex() override;

		// Apply rotation
		void applyRotation();
		bool isDebug = false;
};

#endif

#ifndef __VECTOR4_H
#define __VECTOR4_H

#include <iostream>
#include "Vector3.h"

class Matrix4;

class Vector4
{
public:
	Vector4();
	Vector4(float, float, float);
	Vector4(float, float, float, float);
	Vector4(Vector3, float);
	~Vector4();

	float x;
	float y;
	float z;
	float w;

	Vector4 negative();
	float magnitude();
	void normalise();
	float distance(Vector4 v);
	float dot(Vector4 v);
	Vector4 cross(Vector4 v);

	float operator[](unsigned int idx);
	bool operator==(const Vector4& v1);
	bool operator!=(const Vector4& v1);

	friend std::ostream&operator<< (std::ostream& out, const Vector4 & f);
	Vector4 operator*(const float & lhs) const;
	Vector4 operator*(const Vector4 & lhs) const;
	Vector4 operator*(Matrix4& lhs);
	Vector4 operator+(const Vector4 & lhs) const;
	Vector4 operator+(const float & lhs) const;
	Vector4 operator-(const Vector4 & lhs) const;
	bool operator!=(const Vector4 & lhs) const;
	void operator=(const Vector4& lhs);
	void setValue(unsigned int idx, float value);

	Vector4 operator/(const float & lhs) const;
};

#endif

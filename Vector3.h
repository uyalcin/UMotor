#ifndef __VECTOR3_H
#define __VECTOR3_H

#include <iostream>

class Matrix;
class Vector4;

class Vector3
{
public:
	Vector3();
	Vector3(float, float, float);
	~Vector3();

	float x;
	float y;
	float z;

	Vector3 negative();
	float magnitude();
	void normalise();
	float distance(Vector3 v);
	float dot(Vector3 v);
	Vector3 cross(Vector3 v);

	float operator[](unsigned int idx);
	bool operator==(const Vector3& v1);
	bool operator!=(const Vector3& v1);

	friend std::ostream&operator<< (std::ostream& out, const Vector3 & f);
	Vector3 operator*(const float & lhs) const;
	Vector3 operator*(const Vector3 & lhs) const;
	Vector3 operator*(Matrix& lhs);
	Vector3 operator+(const Vector3 & lhs) const;
	Vector3 operator+(const float & lhs) const;
	Vector3 operator-(const Vector3 & lhs) const;
	bool operator!=(const Vector3 & lhs) const;
	void operator=(const Vector3& lhs);
	void operator=(const Vector4& lhs);
	void setValue(unsigned int idx, float value);

	Vector3 operator/(const float & lhs) const;
};

#endif

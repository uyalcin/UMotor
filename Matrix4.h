#ifndef __MATRIX4_H
#define __MATRIX4_H

#include "Vector4.h"

// Definition of the matrix
// Vector4(a, b, c, d)
// Vector4(e, f, g, h)
// Vector4(i, j, k, l)
// Vector4(m, n, o, p)
// Matrix4x4:
// ( a		b	  c	d)
// ( e		f	  g	h)
// ( i		j	  k	l)
// ( m		n	  o	p)

class Matrix4
{
public:
	Matrix4();
	Matrix4(Vector4, Vector4, Vector4, Vector4);
	~Matrix4();

	Vector4 v1;
	Vector4 v2;
	Vector4 v3;
	Vector4 v4;

	Vector4 operator[](unsigned int idx);
	friend std::ostream&operator<< (std::ostream& out, Matrix4 & f);
	Matrix4 operator+(Matrix4 & lhs);
	Matrix4 operator-(Matrix4 & lhs);
	Matrix4 operator*(const float & lhs);
	Matrix4 operator*(Matrix4 & lhs);
	Vector4 operator*(Vector4 & lhs);
	void setValue(int i, int j, float value);
	float getValue(int i, int j);
};
#endif

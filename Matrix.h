#ifndef __MATRIX_H
#define __MATRIX_H

#include "Vector3.h"

class Matrix
{
public:
	Matrix();
	Matrix(Vector3, Vector3, Vector3);
	~Matrix();

	Vector3 v1;
	Vector3 v2;
	Vector3 v3;

	Vector3 operator[](unsigned int idx);
	friend std::ostream&operator<< (std::ostream& out, Matrix & f);
	Matrix operator+(Matrix & lhs);
	Matrix operator-(Matrix & lhs);
	Matrix operator*(const float & lhs);
	Matrix operator*(Matrix & lhs);
	void setValue(int i, int j, float value);
	float getValue(int i, int j);
};
#endif

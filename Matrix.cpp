#include "Matrix.h"

Matrix::Matrix()
{
	v1 = Vector3(1, 0, 0);
	v2 = Vector3(0, 1, 0);
	v3 = Vector3(0, 0, 1);
}

Matrix::Matrix(Vector3 v1, Vector3 v2, Vector3 v3):
	v1(v1),
	v2(v2),
	v3(v3)
{
}

Matrix::~Matrix()
{
}

Vector3 Matrix::operator[](unsigned int idx)
{
	switch (idx)
	{
	case 0:
		return v1;
		break;
	case 1:
		return v2;
		break;
	case 2:
		return v3;
		break;
	default:
		return Vector3(-1, -1, -1);
		break;
	}
}

Matrix Matrix::operator+(Matrix & lhs)
{
	return Matrix(v1 + lhs.v1, v2 + lhs.v2, v3 + lhs.v3);
}

Matrix Matrix::operator-(Matrix & lhs)
{
	return Matrix(v1 - lhs.v1, v2 - lhs.v2, v3 - lhs.v3);
}

void Matrix::setValue(int i, int j, float value)
{
	switch (i)
	{
		case 0:
			v1.setValue(j, value);
			break;
		case 1:
			v2.setValue(j, value);
			break;
		case 2:
			v3.setValue(j, value);
			break;
	}
}

float Matrix::getValue(int i, int j)
{
	return (*this)[i][j];
}

Matrix Matrix::operator*(Matrix & lhs)
{
	Matrix mul;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float sum = 0.0f;
			for(int k = 0; k < 3; k++)
				sum += (*this)[i][k] * lhs[k][j];
			mul.setValue(i, j, sum);
		}
	}
	return mul;
}

Vector3 Matrix::operator*(Vector3 & lhs)
{
	Vector3 v;
	for (int i = 0; i < 3; i++)
	{
		float sum = 0.0f;
		for(int k = 0; k < 3; k++)
			sum += (*this)[i][k] * lhs[k];
		v.setValue(i, sum);
	}
	return v;
}


std::ostream & operator<<(std::ostream & out, Matrix & m)
{
	out << "Matrix : \n" << m.v1 << "\n" << m.v2 << "\n" << m.v3;
	return out;
}

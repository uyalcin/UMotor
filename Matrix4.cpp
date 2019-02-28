#include "Matrix4.h"
#include "Vector4.h"

Matrix4::Matrix4()
{
	v1 = Vector4(1, 0, 0, 0);
	v2 = Vector4(0, 1, 0, 0);
	v3 = Vector4(0, 0, 1, 0);
	v4 = Vector4(0, 0, 0, 1);
}

Matrix4::Matrix4(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4):
	v1(v1),
	v2(v2),
	v3(v3),
	v4(v4)
{
}

Matrix4::~Matrix4()
{
}

Vector4 Matrix4::operator[](unsigned int idx)
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
	case 3:
		return v4;
		break;
	default:
		return Vector4(-1, -1, -1, -1);
		break;
	}
}

Matrix4 Matrix4::operator+(Matrix4 & lhs)
{
	return Matrix4(v1 + lhs.v1, v2 + lhs.v2, v3 + lhs.v3, v4 + lhs.v4);
}

Matrix4 Matrix4::operator-(Matrix4 & lhs)
{
	return Matrix4(v1 - lhs.v1, v2 - lhs.v2, v3 - lhs.v3, v4 - lhs.v4);
}

void Matrix4::setValue(int i, int j, float value)
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
		case 3:
			v4.setValue(j, value);
			break;
	}
}

float Matrix4::getValue(int i, int j)
{
	return (*this)[i][j];
}

Matrix4 Matrix4::operator*(Matrix4 & lhs)
{
	Matrix4 mul;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;
			for(int k = 0; k < 4; k++)
				sum += (*this)[i][k] * lhs[k][j];
			mul.setValue(i, j, sum);
		}
	}
	return mul;
}

Vector4 Matrix4::operator*(Vector4 & lhs)
{
	Vector4 v;
	for (int i = 0; i < 4; i++)
	{
		float sum = 0.0f;
		for(int k = 0; k < 4; k++)
			sum += (*this)[i][k] * lhs[k];
		v.setValue(i, sum);
	}
	return v;
}

std::ostream & operator<<(std::ostream & out, Matrix4 & m)
{
	out << "Matrix : \n" << m.v1 << "\n" << m.v2 << "\n" << m.v3 << "\n" << m.v4;
	return out;
}

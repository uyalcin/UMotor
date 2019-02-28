//#include "stdafx.h"
#include <math.h>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

Vector3::Vector3(): Vector3(0, 0, 0)
{
}


Vector3::Vector3(float x, float y, float z):
	x(x),
	y(y),
	z(z)
{

}

Vector3::~Vector3()
{
}

Vector3 Vector3::negative()
{
	return Vector3(-x, -y, -z);
}

float Vector3::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::normalise()
{
	float magnitude = this->magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

float Vector3::distance(Vector3 v)
{
	return (*this - v).magnitude();
}

float Vector3::dot(Vector3 v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(Vector3 v)
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector3::operator[](unsigned int idx)
{
	switch (idx)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	default:
		std::cout << "Out of the Vector !" << std::endl;
		return -1;
		break;
	}
}

bool Vector3::operator==(const Vector3 & v1)
{
	return x == v1.x && y == v1.y && z == v1.z;
}

bool Vector3::operator!=(const Vector3 & v1)
{
	return !(*this == v1);
}

std::ostream & operator<<(std::ostream & out, const Vector3 & f)
{
	out << "Vector3 : (" << f.x << ", " << f.y << ", " << f.z << ")";
	return out;
}

Vector3 Vector3::operator*(const float & lhs) const 
{
	return Vector3(x * lhs, y * lhs, z * lhs);
}

Vector3 Vector3::operator*(const Vector3 & lhs) const
{
	return Vector3(x * lhs.x, y * lhs.y, z * lhs.z);
}

Vector3 Vector3::operator+(const Vector3 & lhs) const
{
	return Vector3(x + lhs.x, y + lhs.y, z + lhs.z);
}

Vector3 Vector3::operator+(const float & lhs) const
{
	return Vector3(x + lhs, y + lhs, z + lhs);
}

Vector3 Vector3::operator-(const Vector3 & lhs) const
{
	return Vector3(x - lhs.x, y - lhs.y, z - lhs.z);
}

Vector3 Vector3::operator/(const float & lhs) const
{
	return Vector3(x / lhs, y / lhs, z / lhs);
}

void Vector3::operator=(const Vector3& lhs)
{
	x = lhs.x;
	y = lhs.y;
	z = lhs.z;
}

void Vector3::operator=(const Vector4& lhs)
{
	x = lhs.x;
	y = lhs.y;
	z = lhs.z;
}

bool Vector3::operator!=(const Vector3 & lhs) const
{
	return !(x == lhs.x && y == lhs.y && z == lhs.z);
}

void Vector3::setValue(unsigned int idx, float value)
{
	switch (idx)
	{
		case 0:
			x = value;
			break;
		case 1:
			y = value;
			break;
		case 2:
			z = value;
			break;
		default:
			std::cout << "Out of the Vector !" << std::endl;
			break;
	}
}

Vector3 Vector3::operator*(Matrix& lhs)
{
	Vector3 v;
	for (int i = 0; i < 3; i++)
	{
		float sum = 0.0f;
		for(int k = 0; k < 3; k++)
			sum += (*this)[k] * lhs.getValue(k, i);
		v.setValue(i, sum);
	}
	return v;
}

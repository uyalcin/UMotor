//#include "stdafx.h"
#include "Vector4.h"

#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

Vector4::Vector4(): Vector4(0, 0, 0, 0)
{
}

Vector4::Vector4(float x, float y, float z):
	x(x),
	y(y),
	z(z),
	w(1)
{

}
Vector4::Vector4(float x, float y, float z, float w):
	x(x),
	y(y),
	z(z),
	w(w)
{

}

Vector4::Vector4(Vector3 v, float w):
	x(v.x),
	y(v.y),
	z(v.z),
	w(w)
{
	
}

Vector4::~Vector4()
{
}

Vector4 Vector4::negative()
{
	return Vector4(-x, -y, -z, -w);
}

float Vector4::magnitude()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

void Vector4::normalise()
{
	float magnitude = this->magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	w /= magnitude;
}

float Vector4::distance(Vector4 v)
{
	return (*this - v).magnitude();
}

float Vector4::dot(Vector4 v)
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::cross(Vector4 v)
{
	//return Vector4(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return Vector4();
}

float Vector4::operator[](unsigned int idx)
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
	case 3:
		return w;
		break;
	default:
		std::cout << "Out of the Vector !" << std::endl;
		return -1;
		break;
	}
}

bool Vector4::operator==(const Vector4 & v1)
{
	return x == v1.x && y == v1.y && z == v1.z && w == v1.w;
}

bool Vector4::operator!=(const Vector4 & v1)
{
	return !(*this == v1);
}

std::ostream & operator<<(std::ostream & out, const Vector4 & f)
{
	out << "Vector4 : (" << f.x << ", " << f.y << ", " << f.z << ", " << f.w << ")";
	return out;
}

Vector4 Vector4::operator*(const float & lhs) const 
{
	return Vector4(x * lhs, y * lhs, z * lhs, w * lhs);
}

Vector4 Vector4::operator*(const Vector4 & lhs) const
{
	return Vector4(x * lhs.x, y * lhs.y, z * lhs.z, w * lhs.w);
}

Vector4 Vector4::operator+(const Vector4 & lhs) const
{
	return Vector4(x + lhs.x, y + lhs.y, z + lhs.z, w + lhs.w);
}

Vector4 Vector4::operator+(const float & lhs) const
{
	return Vector4(x + lhs, y + lhs, z + lhs, w + lhs);
}

Vector4 Vector4::operator-(const Vector4 & lhs) const
{
	return Vector4(x - lhs.x, y - lhs.y, z - lhs.z, w - lhs.w);
}

Vector4 Vector4::operator/(const float & lhs) const
{
	return Vector4(x / lhs, y / lhs, z / lhs, w / lhs);
}

void Vector4::operator=(const Vector4& lhs)
{
	x = lhs.x;
	y = lhs.y;
	z = lhs.z;
	w = lhs.w;
}

bool Vector4::operator!=(const Vector4 & lhs) const
{
	return !(x == lhs.x && y == lhs.y && z == lhs.z && w == lhs.w);
}

void Vector4::setValue(unsigned int idx, float value)
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
		case 3:
			w = value;
			break;
		default:
			std::cout << "Out of the Vector !" << std::endl;
			break;
	}
}

Vector4 Vector4::operator*(Matrix4& lhs)
{
	Vector4 v;
	for (int i = 0; i < 4; i++)
	{
		float sum = 0.0f;
		for(int k = 0; k < 4; k++)
			sum += (*this)[k] * lhs.getValue(k, i);
		v.setValue(i, sum);
	}
	return v;
}

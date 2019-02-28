#include <iostream>
#include "../Matrix4.h"

int main()
{
	//Matrix m1(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	Vector4 v1(1, 2, 3, 4);
	Matrix4 m2(Vector4(1, 2, 3, 4),
			Vector4(5, 6, 7, 8),
			Vector4(9, 10, 11, 12),
			Vector4(13, 14, 15, 16));
	
	//Matrix m3 = m1 * m2;
	std::cout << m2 * v1 << std::endl;
	return 0;
}

#include <iostream>
#include "../Matrix.h"
#include "../Vector3.h"

int main()
{
	Matrix m1(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	Matrix m2(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	
	Matrix m3 = m1 * m2;
	std::cout << m3 << std::endl;
	return 0;
}

#include <iostream>
#include "../Matrix.h"
#include "../Vector3.h"

int main()
{
	Matrix m1(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	Vector3 v1(1, 2, 3);
	//Matrix m2(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));
	
	//Matrix m3 = m1 * m2;
	Vector3 v2 = v1 * m1;
	std::cout << v2 << std::endl;
	return 0;
}

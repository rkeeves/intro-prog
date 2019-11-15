#include <iostream>

int main(int argc, char** argv)
{
	int i0 = 7;
	int* p1 = &i0;
	std::cout << p1 << " " << *p1 << std::endl;
	return 0;
}
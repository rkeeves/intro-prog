#include <iostream>

int main(int argc, char** argv)
{
	int *parr = new int[10];
	for(int i = 0; i < 10; ++i){
		std::cout << parr[i] << std::endl;
	}
	delete[] parr;
	return 0;
}
#include <iostream>

void print_array10(const int * parr){
	for(int i = 0; i < 10; ++i){
		std::cout << parr[i] << std::endl;
	}
}

int main(int argc, char** argv)
{
	int *parr = new int[10];
	print_array10(parr);
	delete[] parr;
	return 0;
}
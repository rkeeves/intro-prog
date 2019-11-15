#include <iostream>

void print_array(std::ostream& os, const int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		os << parr[i] << std::endl;
	}
}

void init_array_incr(int * parr, size_t sz, int first){
	for(int i = 0; i < sz; ++i){
		parr[i] = first + i;
	}
}

int main(int argc, char** argv)
{
	int *parr = new int[11];
	init_array_incr(parr,11,100);
	print_array(std::cout,parr,11);
	delete[] parr;
	return 0;
}
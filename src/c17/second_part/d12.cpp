#include <iostream>

void print_array(const int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		std::cout << parr[i] << std::endl;
	}
}

void fill_array_twopowers(int * parr, size_t sz){
	int v = 1;
	for(int i = 0; i < sz; ++i){
		if(i != 0)
			v = v << 1;
		parr[i] = v;
	}
}

void copy_array(const int * from, int * to, size_t sz){
	for(int i = 0; i < sz; ++i){
		to[i] = from[i];
	}
}

int main(int argc, char** argv)
{
	int *p1 = new int[10];
	int *p2 = new int[10];
	fill_array_twopowers(p1,10);
	print_array(p1,10);
	copy_array(p1,p2,10);
	print_array(p2,10);
	delete[] p1;
	delete[] p2;
	return 0;
}
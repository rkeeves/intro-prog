#include <iostream>

void print_array(const int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		std::cout << parr[i] << std::endl;
	}
}

int main(int argc, char** argv)
{
	int i0 = 7;
	int* p1 = &i0;
	std::cout << p1 << " " << *p1 << std::endl;
	int *arr = new int[7];
	int v = 1;
	for(int i = 0; i < 7; ++i){
		if(i != 0)
			v = v << 1;
		arr[i] = v;
	}
	int* p2 = arr;
	std::cout << p2 << " " << *p2 << std::endl;
	print_array(arr,7);
	int* p3 = p2;
	p1 = p2;
	delete[] arr;
	return 0;
}
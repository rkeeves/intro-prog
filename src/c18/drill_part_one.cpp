#include <iostream>
#include <vector>
#include <algorithm>
int ga[10] = {1,2,4,8,16,32,64,128,256,512};

void print_array(std::ostream& os, const int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		os << parr[i] << std::endl;
	}
}

void copy_array(const int * from, int * to, size_t sz){
	for(int i = 0; i < sz; ++i){
		to[i] = from[i];
	}
}

void f(int* parr, int n)
{
	int la[10];
	copy_array(ga,la,10);
	print_array(std::cout,la,10);
	int* ptemp = new int[n];
	copy_array(parr,ptemp,10);
	print_array(std::cout,ptemp,10);
	delete[] ptemp;
}

int fact(int n){
	int buf = 1;
	for(int i = 0; i < n; ++i){
		buf *= i+1;
	}
	return buf;
}

void fill_array_factorials(int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		parr[i] = fact(i+1);
	}
}

int main(int argc, char** argv)
{
	f(ga,10);
	int aa[10];
	fill_array_factorials(aa,10);
	f(aa,10);
	return 0;
}
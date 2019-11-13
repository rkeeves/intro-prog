#include "my.h"
#include "../std_lib_facilities.h"

void print(int i){
	std::cout << i << std::endl;
}

void print_foo(){
	print(foo);
}
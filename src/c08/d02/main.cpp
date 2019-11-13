#include <iostream>	// cout and i/ostream

void swap_v(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int &a, int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// Compile time error.
// Cause: Const referenced data cannot be changed
/*
void swap_cr(const int &a, const int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}
*/

// This one is made up by me
// Caller cannot observe the state of the data passed by &&,
// but callee can modify it.
void swap_rr(int && a, int && b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}


typedef void (*SwapperFn)(int,int);

void test_swap_v(){
	int x  = 7;
	int y = 9;
	swap_v(x,y);
	swap_v(7,9);
	const int cx = 7;
	const int cy = 9;
	swap_v(cx,cy);
	swap_v(7.7,9.9);
	double dx = 7.7;
	double dy = 9.9;
	swap_v(dx,dy);
	swap_v(7.7,9.9);
}

void test_swap_r(){
	int x  = 7;
	int y = 9;
	swap_r(x,y);
	/* only lvalue can be referenced
	swap_r(7,9);
	*/
	/* These are consts
	const int cx = 7;
	const int cy = 9;
	swap_r(cx,cy);
	*/
	/* These are rvalues
	swap_r(7.7,9.9);
	*/
	/* Wont work, type converted from a double lvalue to an int rvalue,
	but function needs an lvalue, because we modify it...
	SEE swap_rr FOR HOW TO HANDLE THIS CASE.
	double dx = 7.7;
	double dy = 9.9;
	swap_r(dx,dy);
	*/
	/*T hese are rvalues
	swap_r(7.7,9.9);
	*/
}

void test_swap_rr(){
	swap_rr(7,9);
	double dx = 7.7;
	double dy = 9.9;
	swap_rr(dx,dy);

}

int main(int argc, char **argv){
	test_swap_v();
	test_swap_r();
	test_swap_rr();
  return 0;
}
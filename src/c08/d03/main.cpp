#include <iostream>

namespace X{
	int var;
	void print(){
		std::cout << var << std::endl;
	}
}/* end of namespace X*/
namespace Y{
	int var;
	void print(){
		std::cout << var << std::endl;
	}
}/* end of namespace X*/
namespace Z{
	int var;
	void print(){
		std::cout << var << std::endl;
	}
}/* end of namespace X*/
int main(int argc, char **argv){
	X::var = 7;
	X::print(); // print X.var
	using namespace Y;
	var = 9; // print Y.var
	print();
	{
		using Z::var; 
		using Z::print;
		var = 11;
		print(); // print Z.var
	}
	print(); // print Y.var
	X::print(); // print X.var
	return 0;
}
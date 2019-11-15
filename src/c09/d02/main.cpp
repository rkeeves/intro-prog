#include "date.h"

int main(int argc, char** argv){
	try{
		Date today{1978,6,25};
		Date tomorrow = today;
		tomorrow.add_days(1);
		tomorrow.print();
		std::cout << "Case 1 OK" << std::endl;
	}catch(...){
		std::cout << "Case 1 FAIL" << std::endl;
	}

	try{
		Date t{2004,13,1};
		std::cout << "Case 2 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 2 OK" << std::endl;
	}
	
	try{
		Date t{2004,12,-5};
		std::cout << "Case 3 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 3 OK" << std::endl;
	}
	
	try{
		Date t{2004,12,31};
		t.add_days(1);
		std::cout << "Case 4 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 4 OK" << std::endl;
	}
	return 0;
}
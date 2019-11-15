#include "date.h"

int main(int argc, char** argv){
	try{
		Date today;
		init(today,1978,6,25);
		Date tomorrow = today;
		add_days(tomorrow,1);
		print(tomorrow);
		std::cout << "Case 1 OK" << std::endl;
	}catch(...){
		std::cout << "Case 1 FAIL" << std::endl;
	}

	try{
		Date t;
		init(t,2004,13,1);
		std::cout << "Case 2 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 2 OK" << std::endl;
	}
	
	try{
		Date t;
		init(t,2004,12,-5);
		std::cout << "Case 3 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 3 OK" << std::endl;
	}
	
	try{
		Date t;
		init(t,2004,12,31);
		add_days(t,1);
		std::cout << "Case 4 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 4 OK" << std::endl;
	}
	return 0;
}
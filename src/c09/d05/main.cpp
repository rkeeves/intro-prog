#include <iostream>
#include "chrono.h"

using namespace Chrono;

int main(int argc, char** argv){
	try{
		Date today{1978,Month::jun,25};
		Date tomorrow = today;
		tomorrow.add_day(1);
		std::cout << tomorrow << std::endl;
		std::cout << "Case 1 OK" << std::endl;
	}catch(...){
		std::cout << "Case 1 FAIL" << std::endl;
	}
	
	std::cout << "Case 2 is caught compile time..." << std::endl;
	
	try{
		Date t{2004,Month::dec,-5};
		std::cout << "Case 3 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 3 OK" << std::endl;
	}
	
	try{
		Date t{2004,Month::dec,31};
		t.add_day(1);
		std::cout << "Case 4 FAIL" << std::endl;
	}catch(...){
		std::cout << "Case 4 OK" << std::endl;
	}
	return 0;
}

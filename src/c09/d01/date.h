#include <exception>
#include <iostream>

struct Date{
	int y;
	int m;
	int d;
};



void init(Date& dd, int y, int m, int d){
	if(m < 1 || m > 12) throw std::runtime_error("Month out of range");
	if(d < 1 || d > 31) throw std::runtime_error("Day out of range");
	dd.y= y;
	dd.m= m;
	dd.d= d;
}

void init(Date& dd, const Date& o){
	init(dd,o.y,o.m,o.d);
}

void add_days(Date& dd, int days){
	dd.d+= days;
	if(dd.d < 1 || dd.d > 31) throw std::runtime_error("Day out of range");
}

void print(Date& dd){
	std::cout << dd.y << '-' << dd.m << '-' << dd.d << std::endl;
}
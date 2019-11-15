#include <exception>
#include <iostream>

struct Date{
	Date(int year, int month, int day) : y(year), m(month), d(day)
	{
		validate();
	}
	
	
	
	void validate(){
		if(m < 1 || m > 12) throw std::runtime_error("Month out of range");
		if(d < 1 || d > 31) throw std::runtime_error("Day out of range");
	}
	
	void add_days(int days){
		d+= days;
		validate();
	}
	
	void print() const
	{
		std::cout << y << '-' << m << '-' << d << std::endl;
	}
	
	int year() const { return y; }
	
	int month() const { return m; }
	
	int day() const { return d; }
	
private:
	int y;
	int m;
	int d;
};

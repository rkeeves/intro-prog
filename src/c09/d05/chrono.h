#ifndef MY_CHRONO_H
#define MY_CHRONO_H


#include <exception>
#include <iostream>
#include <map>

namespace Chrono{

enum class Month{
	jan=1,
	feb,
	mar,
	apr,
	may,
	jun,
	jul,
	aug,
	sep,
	oct,
	nov,
	dec
};

class Date{
public:
	class Invalid{};

	Date(int year, Month month, int day);
	
	Date();
	
	int year() const;
	
	Month month() const;
	
	int day() const;
	
	void add_year(int n);
	
	void add_month(int n);
	
	void add_day(int n);
	
private:
	int y;
	Month m;
	int d;
};

bool is_date(int y, Month m, int d);

bool leapyear(int y);

Month next_month(Month m);

unsigned int days_in_month(int year, Month m);

bool operator ==(const Date& a,const Date& b);

bool operator !=(const Date& a,const Date& b);

std::ostream& operator<<(std::ostream& os, const Date& d);

std::istream& operator>>(std::istream& is, Date& d);

} /* end namespace Chrono*/

#endif
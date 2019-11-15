#include "chrono.h"

namespace Chrono{
	Date::Date(int yy, Month mm, int dd) 
	: y(yy), m(mm), d(dd)
	{
		if(!is_date(yy,mm,dd)) throw Invalid{};
	}
	
	const Date& default_date()
	{
		static Date dd {2001,Month::jan,1};
		return dd;
	}
	
	Date::Date()
	: y(default_date().year()),
	m(default_date().month()),
	d(default_date().day())
	{
		
	}
	
	int Date::year() const
	{
		return y;
	}
	
	Month Date::month() const
	{
		return m;
	}
	
	int Date::day() const
	{
		return d;
	}
	void Date::add_day(int n)
	{
		int next = d+n;
		if(next > days_in_month(y,m)){
			throw Invalid{};
		}
		d = next;
		return;
	}
	
	void Date::add_month(int n)
	{
		for(int i = 0; i<n; ++i){
			m = next_month(m);
		}
		unsigned int max = days_in_month(y,m);
		if(d > max){
			d = max;
		}
	}
	
	void Date::add_year(int n)
	{
		y += n;
		unsigned int max = days_in_month(y,m);
		if(d > max){
			d = max;
		}
	}
	
	bool is_date(int y, Month m, int d)
	{
		if(d<=0) return false;
		if(m<Month::jan || Month::dec < m) return false;
		if(days_in_month(y,m) < d) return false;
		return true;
	}
	
	bool leapyear(int y)
	{
		return (y % 4 == 0);
	}
	
	bool operator==(const Date& a, const Date& b)
	{
		return 	a.year() == b.year() 
						&& a.month() == b.month()
						&& a.day() == b.day();
	}
	
	bool operator!=(const Date& a, const Date& b)
	{
		return 	!(a==b);
	}
	
	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		os << '(' << d.year()
							<< ',' << static_cast<int>(d.month())
							<< ',' << d.day() << ')';
		return os;
	}
	
	std::istream& operator>>(std::istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if(!is) return is;
		if(ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')')
		{
			is.clear(std::ios_base::failbit);
			return is;
		}
		dd = Date(y, Month(m),d);
		return is;
	}
		
	Month next_month(Month m){
		if(m == Month::dec){
			return Month::jan;
		}else{
			return Month(static_cast<int>(m) + 1);
		}
	}
	
	unsigned int days_in_month(int year, Month m){
		switch(m)
		{
				case Month::feb:
					return (leapyear(year))?29:28;
				case Month::apr: case Month::jun: case Month::sep: case Month::nov:	
					return 30;
				default:
					return 31;
		}
	}

}/* end of namespace Chrono*/
#include <exception>
#include <iostream>
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

class Year{
	static const int min = 1800;
	static const int max = 2200;
	public:
	class Invalid{};
	Year(int x) : y(x) 
	{
		if(x<min || x>max) throw Invalid{};
	
	}
	int year() const { return y;}
	private:
	int y;
};

class Date{
public:
	Date(Year year, Month month, int day) : y(year), m(month), d(day)
	{
		validate();
	}
	
	
	
	void validate(){
		if(d < 1 || d > 31) throw std::runtime_error("Day out of range");
	}
	
	void add_days(int days){
		d+= days;
		validate();
	}
	
	void print() const
	{
		std::cout << y.year() << '-' << static_cast<int>(m) << '-' << d << std::endl;
	}
	
	int year() const { return y.year(); }
	
	Month month() const { return m; }
	
	int day() const { return d; }
	
private:
	Year y;
	Month m;
	int d;
};

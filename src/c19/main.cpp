#include <iostream>
#include <string>
#include <vector>

#include "custom.h"

int main(int argc, char** argv)
{
	S<int> s_i(1);
	S<char> s_c('a');
	S<double> s_d(3.14);
	S<std::string> s_s("aa");
	S<std::vector<int>> s_v({ 1 });
	{
		std::cout << s_i.get() << std::endl;
		std::cout << s_c.get() << std::endl;
		std::cout << s_d.get() << std::endl;
		std::cout << s_s.get() << std::endl;
		for(auto& e : s_v.get())
			std::cout << e << std::endl;
	}
	{
		s_i = 8;
		std::cout << s_i.get() << std::endl;
	}
	{
		std::cout << "Enter an int " << std::endl;
		read_val<int>(s_i.get());
		std::cout << s_i.get() << std::endl;
		std::cout << "Enter a char " << std::endl;
		read_val<char>(s_c.get());
		std::cout << s_c.get() << std::endl;
		std::cout << "Enter a double " << std::endl;
		read_val<double>(s_d.get());
		std::cout << s_d.get() << std::endl;
				std::cout << "Enter a string " << std::endl;
		read_val<std::string>(s_s.get());
		std::cout << s_s.get() << std::endl;
	}
}
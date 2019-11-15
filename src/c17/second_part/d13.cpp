#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv)
{
	std::vector<int> v0(10);
	bool first = true;
	int last = 1;
	std::generate(v0.begin(), v0.end(), 
	[&last, &first]()->int
	{ if(first)
			first = false;
		else
			last = last << 1;
		return last;
	});
	std::cout << "v0 " << std::endl;
	std::for_each(v0.begin(), v0.end(), [](int &n){std::cout<<n<<std::endl;});
	std::vector<int> v1(v0);
	std::cout << "v1 " << std::endl;
	std::for_each(v1.begin(), v1.end(), [](int &n){std::cout<<n<<std::endl;});
	return 0;
}
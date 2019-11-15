#include <iostream>
#include <vector>
#include <algorithm>

void do_vec(size_t sz)
{
	std::cout << "do_vec " << sz << std::endl;
	std::vector<int> v(sz);
	int last = 100;
	std::generate(v.begin(), v.end(), [&last]()->int{ return last++;});
	std::for_each(v.begin(), v.end(), [](int &n){std::cout<<n<<std::endl;});
}

int main(int argc, char** argv)
{
	
	do_vec(10);
	do_vec(11);
	do_vec(20);
	return 0;
}
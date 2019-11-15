#include <iostream>
#include <vector>
#include <algorithm>
std::vector<int> ga = {1,2,4,8,16,32,64,128,256,512};

void print_vec(std::ostream& os, const int * parr, size_t sz){
	for(int i = 0; i < sz; ++i){
		os << parr[i] << std::endl;
	}
}

void copy_array(const int * from, int * to, size_t sz){
	for(int i = 0; i < sz; ++i){
		to[i] = from[i];
	}
}

void f(const std::vector<int>& v)
{
	std::vector<int> la(ga);
	std::for_each(la.begin(), la.end(), [](int &n){std::cout<<n<<std::endl;});
	std::vector<int> t(v);
	std::for_each(t.begin(), t.end(), [](int &n){std::cout<<n<<std::endl;});
}

int fact(int n){
	int buf = 1;
	for(int i = 0; i < n; ++i){
		buf *= i+1;
	}
	return buf;
}

void fill_factorials(std::vector<int>& v){
	for(int i = 0; i < v.size(); ++i){
		v[i] = fact(i+1);
	}
}

int main(int argc, char** argv)
{
	f(ga);
	std::vector<int> aa(10);
	fill_factorials(aa);
	f(aa);
	return 0;
}
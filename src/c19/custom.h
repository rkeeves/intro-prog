#ifndef CUSTOM_H
#define CUSTOM_H

#include <string>
#include <iostream>

template<typename T>
class S{
	
public:
	S(T v) : val(v){}
	
	const T& get() const;
	
	T& get(){ return val; }
	
	void operator=(const T&o)
	{
		val = o;
	}
	

	
private:
	T val;
};

template<typename T>
const T& S<T>::get() const{ return val; }

template<typename T>
void read_val(T& v);

template<>
void read_val<int>(int& v)
{
	int t;
	std::cin >> t;
	v = t;
}

template<>
void read_val<char>(char& v)
{
	char t;
	std::cin >> t;
	v = t;
}

template<>
void read_val<double>(double& v)
{
	double t;
	std::cin >> t;
	v = t;
}

template<>
void read_val<std::string>(std::string& v)
{
	std::string t;
	std::cin >> t;
	v = t;
}


#endif
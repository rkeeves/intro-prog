#include "../std_lib_facilities.h"
#include <limits>
using namespace std;

int main()
{
  double max = std::numeric_limits<int>::min();
  double min = std::numeric_limits<int>::max();
  bool shouldRun = true;
  double a;
  while(shouldRun){
    std::cout << "Please enter a double! To exit type | or x" << std::endl;
    cin >> a;
    if (cin.good()) {
      std::cout << "The number was " << a << ". ";
      if( max < a ){ 
        max = a; std::cout << "The largest so far. ";
      };
      if( min > a ){ 
        min = a; std::cout << "The smallest so far. ";
      };
      std::cout << std::endl;
    }else{
      std::cout << "Exiting program " << std::endl;
      shouldRun = false;
    }
  }
  return 0;
}
#include "../std_lib_facilities.h"
#include <limits>
using namespace std;

int main()
{
  constexpr double FACTOR_M_CM = 100.0;
  constexpr double FACTOR_IN_CM = 2.54;
  constexpr double FACTOR_FT_CM = 12 * FACTOR_IN_CM;
  double max = std::numeric_limits<int>::min();
  double min = std::numeric_limits<int>::max();
  bool shouldRun = true;
  double l;
  bool isBadLunit = false;
  std::string lunit;
  while(shouldRun){
    std::cout << "Please enter a double and a length unit! To exit type | or x" << std::endl;
    cin >> l >> lunit;
    if (cin.good()) {
      isBadLunit = false;
      if(lunit.compare("cm")==0){
        //nothing to do, base unit is cm
      }else if(lunit.compare("m")==0){
        l *= FACTOR_M_CM;
      }else if(lunit.compare("in")==0){
        l *= FACTOR_IN_CM;
      }else if(lunit.compare("ft")==0){
        l *= FACTOR_FT_CM;
      }else{
        isBadLunit = true;
      }
      if(isBadLunit){
        std::cout << "Unknown length unit " << lunit << ", skipping this round. ";
      }else{
        std::cout << "The length is " << l << "cm. ";
        if( max < l ){ max = l; std::cout << "The largest so far. ";};
        if( min > l ){  min = l; std::cout << "The smallest so far. ";};
        std::cout << std::endl;
      }
    }else{
      std::cout << "Exiting program " << std::endl;
      shouldRun = false;
    }
  }
  return 0;
}
#include <iostream>
#include <vector>
#include <limits>

int main()
{
  constexpr double FACTOR_CM_M = 1.0/100.0;
  constexpr double FACTOR_IN_M = 2.54/100.0;
  constexpr double FACTOR_FT_M = 12 * FACTOR_IN_M;
  double max = std::numeric_limits<int>::min();
  double min = std::numeric_limits<int>::max();
  bool shouldRun = true;
  double l;
  bool isBadLunit = false;
  std::string lunit;
  int count = 0;
  double sum = 0;
  std::vector<double> lvec;
  while(shouldRun){
    std::cout << "Please enter a double and a length unit! To exit type | or x" << std::endl;
    std::cin >> l >> lunit;
    if (std::cin.good()) {
      isBadLunit = false;
      if(lunit.compare("cm")==0){
        l *= FACTOR_CM_M;
      }else if(lunit.compare("m")==0){
        //nothing to do, base unit is m
      }else if(lunit.compare("in")==0){
        l *= FACTOR_IN_M;
      }else if(lunit.compare("ft")==0){
        l *= FACTOR_FT_M;
      }else{
        isBadLunit = true;
      }
      if(isBadLunit){
        std::cout << "Unknown length unit " << lunit << ", skipping this round. ";
      }else{
        count++;
        sum+=l;
        lvec.push_back(l);
        std::cout << "The length is " << l << "m. ";
        if( max < l ){ max = l; std::cout << "The largest so far. ";};
        if( min > l ){  min = l; std::cout << "The smallest so far. ";};
        std::cout << std::endl;
      }
    }else{
      std::cout << "Exiting loop " << std::endl;
      shouldRun = false;
    }
  }
  std::cout << "--------------------" << std::endl << "- Summary" << std::endl << "--------------------"<< std::endl;
  std::cout << "Max " << (max == std::numeric_limits<int>::min() ? 0 : max) << " m" << std::endl;
  std::cout << "Min " << (min == std::numeric_limits<int>::max() ? 0 : min) << " m" << std::endl;
  std::cout << "Sum " << sum << " m" << std::endl;
  std::cout << "Entry Count " << count << std::endl;
  std::cout << "All entries " << std::endl;
  int sz = lvec.size();
  for(int i = 0; i < sz; i++){ 
    std::cout << (i+1) << " : " << lvec[i] << " m" << std::endl;
  }
  return 0;
}
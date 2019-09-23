#include "../std_lib_facilities.h"

using namespace std;

int main()
{
  bool shouldRun = true;
  int a, b;
  bool alteq = true;
  while(shouldRun){
    std::cout << "Please enter two integers! To exit type | or x" << std::endl;
    cin >> a >> b;
    if (cin.good()) {
      if(a == b){
        std::cout << "The numbers are equal" << std::endl;
      }else{
        alteq = a <= b;
        std::cout << "smaller value is " << (alteq ? a : b) << ", larger value is " << (alteq ? b : a) << std::endl;
      }
    }else{
      std::cout << "Exiting program " << std::endl;
      shouldRun = false;
    }
  }
  return 0;
}
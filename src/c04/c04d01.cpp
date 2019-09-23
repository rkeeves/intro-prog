#include "../std_lib_facilities.h"

using namespace std;

int main()
{
  bool shouldRun = true;
  int a, b;
  while(shouldRun){
    std::cout << "Please enter two integers! To exit type '|'" << std::endl;
    cin >> a >> b;
    if (cin.good()) {
      std::cout << "a " << a << ", b " << b << std::endl;
    }else{
      std::cout << "Exiting program " << std::endl;
      shouldRun = false;
    }
  }
  return 0;
}
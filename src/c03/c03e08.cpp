#include "../std_lib_facilities.h"

using namespace std;
  
int main()
{
  int uint;
  cout << "Enter the integer:\n";
  cin >> uint;
  cout << "The number " << uint;
  if(uint % 2 == 0){
    cout << " is even.";
  }else{
    cout << " is odd.";
  }
  cout << endl;
  return 0;
}
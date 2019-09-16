#include "../std_lib_facilities.h"

using namespace std;

string arr[5] = {
  "zero",
  "one",
  "two",
  "three",
  "four"
};

int lins(string arr[], int n, const string &v){
  for(int i = 0; i < n; i++){
    if(arr[i].compare(v)==0){
      return i;
    }
  }
  return -1;
};

int main()
{
  string ustr;
  cout << "Enter the string:\n";
  cin >> ustr;
  int idx = lins(arr,5,ustr);
  if(idx < 0){
    simple_error("Not a number I know");
  }
  cout << "The corresponding number for " << ustr << " is " << idx << endl;
  return 0;
}
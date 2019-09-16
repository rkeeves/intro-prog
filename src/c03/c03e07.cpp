#include "../std_lib_facilities.h"

using namespace std;

void sort(string arr[], int n);
  
int main()
{
  string uarr[3];
  cout << "Enter the first string:\n";
  cin >> uarr[0];
  cout << "Enter the second string:\n";
  cin >> uarr[1];
  cout << "Enter the third string:\n";
  cin >> uarr[2];
  sort(uarr,3);
  cout << "The sorted order of the strings is:" << endl << uarr[0] << ", " << uarr[1] << ", " << uarr[2] << endl;
  return 0;
}

void sort(string arr[], int n){
  int i, j;
  string key;
  for (i = 1; i < n; i++) {  
    key = arr[i];  
    j = i - 1;  
    while (j >= 0 && arr[j].compare(key)) {  
      arr[j + 1] = arr[j];  
      j = j - 1;  
    }  
    arr[j + 1] = key;  
  }  
}
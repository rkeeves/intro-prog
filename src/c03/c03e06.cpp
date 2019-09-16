#include "../std_lib_facilities.h"

using namespace std;

void sort(int arr[], int n);
  
int main()
{
  int uarr[3];
  cout << "Enter the first int:\n";
  cin >> uarr[0];
  cout << "Enter the second int:\n";
  cin >> uarr[1];
  cout << "Enter the third int:\n";
  cin >> uarr[2];
  sort(uarr,3);
  cout << "The sorted order of the integers is:" << endl << uarr[0] << ", " << uarr[1] << ", " << uarr[2] << endl;
  return 0;
}

void sort(int arr[], int n){
  int i, j;
  int key;  
  for (i = 1; i < n; i++) {  
    key = arr[i];  
    j = i - 1;  
    while (j >= 0 && arr[j] > key) {  
      arr[j + 1] = arr[j];  
      j = j - 1;  
    }  
    arr[j + 1] = key;  
  }  
}
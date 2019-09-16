#include "../std_lib_facilities.h"

using namespace std;

struct Currency{
  string singular;
  string plural;
  int centMult;
  Currency(string singular,string plural, int centMult){
    this->singular = singular;
    this->plural = plural;
    this->centMult = centMult;
  };
};

int sumCents(int arr[], int n, Currency curArr[]){
  int tmp = 0;
  for(int i = 0;i < n; i++){
    tmp += arr[i]*curArr[i].centMult;
  }
  return tmp;
}

double sumDollars(int arr[], int n,Currency curArr[]){
  double tmp = 0;
  for(int i = 0;i < n; i++){
    tmp += (double)(arr[i]*curArr[i].centMult)/100.0;
  }
  return tmp;
}

int main()
{
  Currency currency_arr[] = 
  {
    {"penny","pennies",1},
    {"nickel","nickels",5},
    {"dime","dimes",10},
    {"quarter","quarters",25},
    {"half dollar","half dollars",50},
    {"one-dollar coin","one-dollar coins",100}
  };
  int money[6];
  for(int i = 0;i < 6; i++){
    cout << "How many "<<currency_arr[i].plural<<" do you have?"<<endl;
    cin >> money[i];
    if(money[i] < 0){ simple_error("Error: You are in debt!"); }
  }
  for(int i = 0;i < 6; i++){
    cout << "You have " << money[i] << " ";
    if(money[i] == 1){
      cout << currency_arr[i].singular;
    }else{
      cout << currency_arr[i].plural;
    }
    cout << endl;
  }
  int tmpi = sumCents(money,6,currency_arr);
  cout << "You have " << tmpi;
  if(tmpi == 1){
    cout << " cent";
  }else{
    cout << " cents";
  }
  cout << endl;
  double tmpd = sumDollars(money,6,currency_arr);
  cout << "You have $" << tmpd << endl;
  return 0;
}
#include "../std_lib_facilities.h"

using namespace std;

double opplus(double o1, double o2){
  return o1 + o2;
};

double opminus(double o1, double o2){
  return o1 - o2;
};

double opmul(double o1, double o2){
  return o1 * o2;
};

double opdiv(double o1, double o2){
  if(o2 == 0.0){ return 0; }
  return o1 / o2;
};

int main()
{
  string op;
  cout << "Enter the operation:\n";
  cin >> op;
  // https://youtu.be/s6gNo4-1r6k
  double (*oper)(double,double);
  if(op.compare("+")==0){
    oper = opplus;
  }else if(op.compare("-")==0){
    oper = opminus;
  }else if(op.compare("*")==0){
    oper = opmul;
  }else if(op.compare("/")==0){
    oper = opdiv;
  }else{
    simple_error("Not an operation I know");
  }
  double op1, op2;
  cout << "Enter the first operand:\n";
  cin >> op1;
  cout << "Enter the second operand:\n";
  cin >> op2;
  cout << "The result is number for " << oper(op1,op2) << endl;
  return 0;
}
#include "..\helper.h"

int main(void){
  try{
    /*
    int x = 2;
    double d = 5 / (x-2);
    if(d==2*x+0.5)cout<<"Success!\n";
    */
    int x = 2;
    double d = 5 / ((x-2) + 1) - 0.5;
    if(d==2*x+0.5)cout<<"Success!\n";
    return 0;
  }catch(exception &e){
    cerr << "error:" << e.what() << '\n';
    keep_window_open();
    return 1;
  }catch(...){
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
  }
  
}
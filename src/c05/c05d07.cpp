#include "..\helper.h"

int main(void){
  try{
    /*
    if(cond)
      cout << "Success!\n";
    else
      cout << "Fail!\n";
    */
    if(true)
      cout << "Success!\n";
    else
      cout << "Fail!\n";
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
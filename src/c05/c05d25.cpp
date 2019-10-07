#include "..\helper.h"

int main(void){
  try{
    /*
    cin << "Success!\n";
    */
    cout << "Success!\n";
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
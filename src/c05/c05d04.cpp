#include "..\std_lib_facilities.h"

int main(void){
  try{
    /*
    cout << success << '\n';
    */
    cout << "success" << '\n';
    keep_window_open();
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
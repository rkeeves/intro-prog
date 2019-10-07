#include "..\helper.h"

int main(void){
  try{
    /*
    bool c = false;
    if(c)
      cout << "Success!\n";
    else
      cout << "Fail!\n";
    */
    bool c = false;
    if(!c)
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
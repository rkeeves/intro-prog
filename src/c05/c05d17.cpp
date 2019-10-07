#include "..\helper.h"

int main(void){
  try{
    /*
    int x = 2000; char c = x;
    if(c == 2000) cout << "Success!\n";
    */
    int x = 2000; char c = x;
    if(c != 2000) cout << "Success!\n";
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
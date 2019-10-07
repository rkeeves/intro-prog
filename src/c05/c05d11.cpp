#include "..\helper.h"

int main(void){
  try{
    /*
    string s = "ape";
    if(s=="fool")cout < "Success!\n";
    */
    string s = "ape";
    if(s!="fool")cout << "Success!\n";
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
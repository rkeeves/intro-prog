#include "..\helper.h"

int main(void){
  try{
    /*
    string s = "Success!\n";
    for(int i = 0; i<10; ++i){
      cout << s[i];
    }
    */
    string s = "Success!\n";
    for(int i = 0; i<s.size(); ++i){
      cout << s[i];
    }
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
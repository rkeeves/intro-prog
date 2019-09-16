#include "../std_lib_facilities.h"

using namespace std;

int main()
{
  string recipient_name;
  string friend_name;
  char friend_sex;
  string friend_pronoun;
  int recipient_age;
  string dynamic_question;
  //UData input
  cout << "Enter the recipients name:\n";
  cin >> recipient_name;
  cout << "Enter the friends name you want to ask about:\n";
  cin >> friend_name;
  cout << "Enter the code for the friends gender ([m]ale, [f]emale, any other character will result in neutral gender):\n";
  cin >> friend_sex;
  cout << "Enter the age of the recipient:\n";
  cin >> recipient_age;
  if(recipient_age <= 0 || recipient_age > 110){
    // simple_error calls exit with an argument of 1,
    // which terminates the process normally, performing the regular cleanup for terminating programs.
    simple_error("You are kidding!");
  }
  if(friend_sex == 'm'){
    friend_pronoun = "him";
  }else if(friend_sex == 'f'){
    friend_pronoun = "her";
  }else{
    friend_pronoun = "it";
  }
  //Letter out
  cout << "Dear " << recipient_name << "," << endl << endl;
  cout << "\tHow are you? I am fine. I miss you." << endl;
  cout << "We had such a generic event last random." << endl;
  cout << "\tLorem ipsum dolor sit amet, consectetur adipiscing elit." << endl;
  cout << "Quisque venenatis pellentesque rhoncus." << endl;
  cout << "Sed eros arcu, vulputate vitae ligula blandit rhoncus tempus nunc..." << endl;
  cout << "Aenean diam diam, efficitur sollicitudin" << endl;
  cout << "celerisque non, dignissim non nisi." << endl;
  cout << "\tHave you seen " << friend_name << " lately?" << endl;
  cout << "If you see " << friend_name << " please ask " << friend_pronoun << " to call me." << endl;
  cout << '\t';
  if(recipient_age == 17){
    cout << "Next year you will be able to vote." << endl;;
  }else if(recipient_age > 70){
    cout << "I hope you are enjoying your retirement!" << endl;;
  }else if(recipient_age < 12){
    cout << "Next year you will be " << (recipient_age+1) << "." << endl;
  }
  cout << "I know you hate pointless tabs, so I hope you will love this sentence." << endl;
  cout << endl << "Yours sincerely," << endl << endl << endl << "\tJohn Doe" << endl;
  return 0;
}
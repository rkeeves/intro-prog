#include "../std_lib_facilities.h"

using namespace std;

class UnitConverter{
public:
  UnitConverter(double from, double to){this->m_ratio = (from/to);}
  
  inline double from(double v){return v/m_ratio;}
  
  inline double to(double v){return v*m_ratio;}
  
private:
  double m_ratio;
};

int main()
{
  char from_unit_sym;
  double tmp;
  string to_unit_name;
  cout << "Enter the length VALUE:\n";
  cin >> tmp;
  cout << "Enter the length UNIT you want to convert FROM ([k]ilometers, [m]iles):\n";
  cin >> from_unit_sym;
  UnitConverter kmToMiles = UnitConverter(1609,1000);
  if(from_unit_sym == 'k'){
    tmp = kmToMiles.from(tmp);
    to_unit_name = "miles";
  }else if(from_unit_sym == 'm'){
    tmp = kmToMiles.to(tmp);
    to_unit_name = "kilometers";
  }else{
    simple_error("Invalid length unit");
  }
  cout << "Equals " << tmp << " " << to_unit_name << endl;
  return 0;
}
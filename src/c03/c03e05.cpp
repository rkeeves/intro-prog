#include "../std_lib_facilities.h"

using namespace std;

class Solver{
public:
  Solver(float val1, float val2){
    this->m_val_1 = val1;
    this->m_val_2 = val2;
  }
  
  inline double smaller(){return (m_val_1 < m_val_2 ? m_val_1 : m_val_2);}
  
  inline double larger(){return (m_val_1 < m_val_2 ? m_val_2 : m_val_1);}
  
  inline double sum(){return m_val_1+m_val_2;}
  
  inline double difference(){return m_val_1-m_val_2;}
  
  inline double product(){return m_val_1*m_val_2;}
  
  inline double ratioZeroSafe(){ return (m_val_1 == 0 ? 0 : (m_val_1)/(m_val_2));}
  
private:
  double m_val_1;
  
  double m_val_2;
};

int main()
{
  float tmp1;
  float tmp2;
  cout << "Enter the first float:\n";
  cin >> tmp1;
  cout << "Enter the second float:\n";
  cin >> tmp2;
  if(tmp2 == 0.0f){
    simple_error("The second float must be a non-null float");
  }
  Solver sol = Solver(tmp1,tmp2);
  cout << "Smaller " << sol.smaller() << endl;
  cout << "Larger " << sol.larger() << endl;
  cout << "Sum " << sol.sum() << endl;
  cout << "Product " << sol.product() << endl;
  cout << "Ratio (Zero Safe) " << sol.ratioZeroSafe() << endl;
  return 0;
}
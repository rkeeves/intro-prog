#include "../std_lib_facilities.h"

using namespace std;

class Solver{
public:
  Solver(int val1, int val2){
    this->m_val_1 = val1;
    this->m_val_2 = val2;
  }
  
  inline int smaller(){return (m_val_1 < m_val_2 ? m_val_1 : m_val_2);}
  
  inline int larger(){return (m_val_1 < m_val_2 ? m_val_2 : m_val_1);}
  
  inline int sum(){return m_val_1+m_val_2;}
  
  inline int difference(){return m_val_1-m_val_2;}
  
  inline int product(){return m_val_1*m_val_2;}
  
  inline double ratioZeroSafe(){ return (m_val_1 == 0 ? 0 : (((double)(m_val_1))/((double)(m_val_2))));}
  
private:
  int m_val_1;
  
  int m_val_2;
};

int main()
{
  int tmp1;
  int tmp2;
  cout << "Enter the first integer:\n";
  cin >> tmp1;
  cout << "Enter the second integer:\n";
  cin >> tmp2;
  if(tmp2 == 0){
    simple_error("The second int must be a non-null integer");
  }
  Solver sol = Solver(tmp1,tmp2);
  cout << "Smaller " << sol.smaller() << endl;
  cout << "Larger " << sol.larger() << endl;
  cout << "Sum " << sol.sum() << endl;
  cout << "Product " << sol.product() << endl;
  cout << "Ratio (Zero Safe) " << sol.ratioZeroSafe() << endl;
  return 0;
}
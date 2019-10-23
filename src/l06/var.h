#ifndef VAR_H
#define VAR_H

#include <cstddef>
#include <iostream>
#include <string>

namespace calc{
  
  enum class VarKind{
    Nil,
    Bln,
    Int,
    Dbl,
    Str,
    Func,
    Unhandled,
  };
  
  std::ostream& operator<<(std::ostream& os, const calc::VarKind& vk) {
    static const char* const VarKindNames[]{
      "Nil",
      "Bln",
      "Int",
      "Dbl",
      "Str",
      "Unhandled"
    };
    return os << VarKindNames[static_cast<int>(vk)];
  }
  
  class Var{
  public:
    Var(std::nullptr_t) : k(VarKind::Nil), b(false), i(0), d(0.0), s(""){};
    
    Var(bool v) : k(VarKind::Bln), b(v), i(0), d(0.0), s(""){};
    
    Var(int v): k(VarKind::Int), b(false), i(v), d(0.0), s(""){};
    
    Var(double v): k(VarKind::Dbl), b(false), i(0), d(v), s(""){};
    
    Var(std::string v): k(VarKind::Str), b(false), i(0), d(0.0), s(v){};
    
    Var& operator=(Var o)
    {
      k = o.k;
      b = o.b;
      i = o.i;
      d = o.d;
      s = o.s;
      return *this;
    }
    
    template<typename T>
    bool is() const = delete;
    
    template<typename T>
    T get() const = delete;
    
    friend std::ostream& operator<<(std::ostream& os, const Var& v);
    
  private:
  
    VarKind k;
    
    bool b;
    
    int i;
    
    double d;
    
    std::string s;
  };
  
  std::ostream& operator<<(std::ostream& os, const calc::Var& v) {
    return os <<"{ k:"<<v.k<<", b:"<<v.b<<", i:"<<v.i<<", d:"<<v.d<<", s:'"<<v.s<<"' }";
  }
  
  template<>
  bool Var::is<bool>() const 
  {
    return (k==VarKind::Bln);
  }
  
  template<>
  bool Var::is<int>() const 
  {
    return (k==VarKind::Int);
  }
  
  template<>
  bool Var::is<double>() const 
  {
    return (k==VarKind::Dbl);
  }
  
  template<>
  bool Var::is<std::string>() const 
  {
    return (k==VarKind::Str);
  }
  
  template<>
  bool Var::get<bool>() const 
  {
    return b;
  }
  
  template<>
  int Var::get<int>() const 
  {
    return i;
  }
  
  template<>
  double Var::get<double>() const 
  {
    return d;
  }
  
  template<>
  std::string Var::get<std::string>() const 
  {
    return s;
  }
} /* end of namespace calc */
#endif // VAR_H
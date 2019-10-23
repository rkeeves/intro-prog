#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>
#include <exception>
#include <functional>

#include "var.h"
#include "expr.h"

namespace calc{
  class Context;
  
  typedef std::function<Var(const ExprTree &tree, ExprNodeIdx ni, Context &ctx)> NativeFunc;
  
  typedef std::map<std::string, NativeFunc> NativeFuncMap;
  
  typedef std::map<std::string, Var> VarMap;
  
  class Context{
  public:
  
    Context() : parent(nullptr){};
    
    Context(Context* theParent) : parent(theParent){};
    
    void define(const std::string &name, const Var &var);
    
    bool contains(const std::string &name) const;
    
    Var get(const std::string &name) const;
    
    void set(const std::string &name, const Var &var);

    void defineNativeFunction(const std::string &fname, NativeFunc f);
    
    NativeFunc getNativeFunction(const std::string &fname);
    
  private:
    inline bool hasParent() const { return (parent != nullptr);};
    
    VarMap varMap;
    
    NativeFuncMap nativeFuncMap;
    
    Context* parent;
  };
  
  bool Context::contains(const std::string &name) const
  {
    return (varMap.find(name) != varMap.end());
  };
  
  void Context::define(const std::string &name, const Var &var)
  {
    auto it = varMap.find(name);
    if(it != varMap.end()){
      throw std::runtime_error(std::string("Redefinition of variable '")+name+"'!");
    }else{
      varMap.insert ( std::pair<std::string,Var>(name,var) );
    }
  };
  
  Var Context::get(const std::string &name) const
  {
    auto it = varMap.find(name);
    if(it == varMap.end()){
      if(hasParent())
        return parent->get(name);
      else
        throw std::runtime_error(std::string("Unknown variable '")+name+"'!");
    }else{
      return it->second;
    }
    
  };
  
  void Context::set(const std::string &name, const Var &var)
  {
    auto it = varMap.find(name);
    if(it == varMap.end()){
      if(hasParent())
        parent->set(name,var);
      else
        define(name,var);
    }else{
      it->second = var;
    }
  };
  
  void Context::defineNativeFunction(const std::string &fname, NativeFunc f)
  {
    auto it = nativeFuncMap.find(fname);
    if(it != nativeFuncMap.end()){
      throw std::runtime_error(std::string("Redefinition of nativeFunction '")+fname+"'!");
    }else{
      nativeFuncMap.insert ( std::pair<std::string,NativeFunc>(fname,f) );
    }
  };
  
  NativeFunc Context::getNativeFunction(const std::string &fname){
    auto it = nativeFuncMap.find(fname);
    if(it == nativeFuncMap.end()){
      throw std::runtime_error(std::string("Unknown nativeFunction '")+fname+"'!");
    }else{
      return it->second;
    }
  }
} /* end of namespace calc */
#endif // CONTEXT_H
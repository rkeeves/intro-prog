#ifndef CALCLIB_H
#define CALCLIB_H

#include <cstddef>
#include <iostream>
#include <string>

#include "eval.h"

namespace calc{
  void printVar(const Var &var){
    if(var.is<bool>()){
      std::cout<< var.get<bool>();
    }else if(var.is<int>()){
      std::cout<< var.get<int>();
    }else if(var.is<double>()){
      std::cout<< var.get<double>();
    }else if(var.is<std::string>()){
      std::cout<< var.get<std::string>();
    }else{
      std::cout<< var;
    }    
  }
  
  Var print(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    size_t argcount = tree.getChildCount(ni)-1;
    bool first = true;
    for(size_t i = 0; i < argcount;++i){
      if(first)
      {first = false; std::cout<< "[PRINT] ";}
      else
      {std::cout<< ", ";}
      Var v = evalExpression(tree,tree.getChildAt(ni,i+1),ctx);
      printVar(v);
    }
    std::cout<< std::endl;
    return Var(nullptr);
  }
  

} /* end of namespace calc */
#endif // CALCLIB_H
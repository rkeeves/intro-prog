#ifndef EVAL_H
#define EVAL_H

#include <sstream>

#include "expr.h"
#include "context.h"


namespace calc{
  
  Var evalExpression(const ExprTree &tree, ExprNodeIdx ni, Context &ctx);
  
  Var negate(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=1){
      throw std::runtime_error("Negation bad number of arguments");
    }
    ExprNodeIdx nn = tree.getChildAt(ni,0);
    Var var = evalExpression(tree,nn,ctx);
    if(var.is<bool>()){
      bool v = ! (var.get<bool>());
      return Var(v);
    }else if(var.is<int>()){
      int v = -(var.get<int>());
      return Var(v);
    }else if(var.is<double>()){
      int v = -(var.get<double>());
      return Var(v);
    }else{
      throw std::runtime_error("Negate bad argument");
    }
  }
  
  Var add(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=2){
      throw std::runtime_error("Addition bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    Var var2 = evalExpression(tree,tree.getChildAt(ni,1),ctx);
    if(var1.is<int>()){
      if(var2.is<int>()){
        return Var(var1.get<int>() + var2.get<int>());
      }else if(var2.is<double>()){
        return Var(var2.get<double>() + static_cast<double>(var1.get<int>()));
      }else{
        throw std::runtime_error("Addition bad second argument");
      }
    }else if(var1.is<double>()){
      if(var2.is<int>()){
        return Var(var1.get<double>() + static_cast<double>(var2.get<int>()));
      }else if(var2.is<double>()){
        return Var(var2.get<double>() +var1.get<double>());
      }else{
        throw std::runtime_error("Addition bad second argument");
      }
    }else if(var1.is<std::string>()){
      if(var2.is<std::string>()){
        return Var(var1.get<std::string>() +var2.get<std::string>());
      }else if(var2.is<int>()){
        std::stringstream ss;
        ss<<var1.get<std::string>()<<var2.get<int>();
        return Var(ss.str());
      }else if(var2.is<double>()){
        std::stringstream ss;
        ss<<var1.get<std::string>()<<var2.get<double>();
        return Var(ss.str());
      }else if(var2.is<bool>()){
         std::stringstream ss;
        ss<<var1.get<std::string>()<<var2.get<bool>();
        return Var(ss.str());
      }else{
        throw std::runtime_error("Addition bad second argument");
      }
    }else{
      throw std::runtime_error("Addition bad first argument");
    }
  }
  
  Var subtract(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=2){
      throw std::runtime_error("Subtraction bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    Var var2 = evalExpression(tree,tree.getChildAt(ni,1),ctx);
    if(var1.is<int>()){
      if(var2.is<int>()){
        return Var(var1.get<int>() - var2.get<int>());
      }else if(var2.is<double>()){
        return Var(static_cast<double>(var1.get<int>()) - var2.get<double>());
      }else{
        throw std::runtime_error("Subtraction bad second argument");
      }
    }else if(var1.is<double>()){
      if(var2.is<int>()){
        return Var(var1.get<double>() - static_cast<double>(var2.get<int>()));
      }else if(var2.is<double>()){
        return Var(var2.get<double>() - var1.get<double>());
      }else{
        throw std::runtime_error("Subtraction bad second argument");
      }
    }else{
      throw std::runtime_error("Subtraction bad first argument");
    }
  }
  
  Var multiply(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=2){
      throw std::runtime_error("Multiplication bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    Var var2 = evalExpression(tree,tree.getChildAt(ni,1),ctx);
    if(var1.is<int>()){
      if(var2.is<int>()){
        return Var(var1.get<int>() * var2.get<int>());
      }else if(var2.is<double>()){
        return Var(static_cast<double>(var1.get<int>()) * var2.get<double>());
      }else{
        throw std::runtime_error("Multiplication bad second argument");
      }
    }else if(var1.is<double>()){
      if(var2.is<int>()){
        return Var(var1.get<double>() * static_cast<double>(var2.get<int>()));
      }else if(var2.is<double>()){
        return Var(var2.get<double>() * var1.get<double>());
      }else{
        throw std::runtime_error("Multiplication bad second argument");
      }
    }else{
      throw std::runtime_error("Multiplication bad first argument");
    }
  }
  
  Var divide(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=2){
      throw std::runtime_error("Multiplication bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    Var var2 = evalExpression(tree,tree.getChildAt(ni,1),ctx);
    if(var1.is<int>()){
      if(var2.is<int>()){
        if(var2.get<int>() == 0){throw std::runtime_error("Multiplication second argument was 0");}
        return Var(static_cast<double>(var1.get<int>()) / static_cast<double>(var2.get<int>()));
      }else if(var2.is<double>()){
        if(var2.get<double>() == 0){throw std::runtime_error("Multiplication second argument was 0");}
        return Var(static_cast<double>(var1.get<int>()) / var2.get<double>());
      }else{
        throw std::runtime_error("Multiplication bad second argument");
      }
    }else if(var1.is<double>()){
      if(var2.is<int>()){
        if(var2.get<int>() == 0){throw std::runtime_error("Multiplication second argument was 0");}
        return Var(var1.get<double>() / static_cast<double>(var2.get<int>()));
      }else if(var2.is<double>()){
        if(var2.get<int>() == 0){throw std::runtime_error("Multiplication second argument was 0");}
        return Var(var2.get<double>() / var1.get<double>());
      }else{
        throw std::runtime_error("Multiplication bad second argument");
      }
    }else{
      throw std::runtime_error("Multiplication bad first argument");
    }
  }
    
  
  
  Var assignment(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)!=2){
      throw std::runtime_error("Assignment bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    Var var2 = evalExpression(tree,tree.getChildAt(ni,1),ctx);
    if(var1.is<std::string>()){
      ctx.set(var1.get<std::string>(),var2);
      return var2;
    }
    throw std::runtime_error("Assignment bad first argument");
  }
  
  Var call(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    if(tree.getChildCount(ni)<1){
      throw std::runtime_error("Call bad number of arguments");
    }
    Var var1 = evalExpression(tree,tree.getChildAt(ni,0),ctx);
    if(var1.is<std::string>()){
      return ctx.getNativeFunction(var1.get<std::string>())(tree,ni,ctx);
    }
    throw std::runtime_error("Call bad first argument");
  }
    
  Var evalExpression(const ExprTree &tree, ExprNodeIdx ni, Context &ctx){
    ExprType nt = tree.getExprType(ni);
    switch(nt) {
      case ExprType::NilLiteral: 
      {
        return Var(nullptr);
      }break;
      case ExprType::BlnLiteral: 
      {
        bool v = (tree.getRaw(ni).compare("true") == 0) ? true : false;
        return Var(v);
      }break;
      case ExprType::IntLiteral: 
      {
        int v;
        std::istringstream(tree.getRaw(ni)) >> v;
        return Var(v);
      }break;
      case ExprType::DblLiteral: 
      {
        double v;
        std::istringstream(tree.getRaw(ni)) >> v;
        return Var(v);
      }break;
      case ExprType::StrLiteral: 
      {
        return Var(tree.getRaw(ni));
      }break;
      case ExprType::Symbol: 
      {
        return ctx.get(tree.getRaw(ni));
      }break;
      case ExprType::Identity: 
      {
        return evalExpression(tree, tree.getChildAt(ni,0),ctx);
      }break;
      case ExprType::Negate: 
      {
        return negate(tree,ni,ctx);
      }break;
      case ExprType::Add: 
      {
        return add(tree,ni,ctx);
      }break;
      case ExprType::Subtract: 
      {
        return subtract(tree,ni,ctx);
      }break;
      case ExprType::Multiply: 
      {
        return multiply(tree,ni,ctx);
      }break;
      case ExprType::Divide: 
      {
        return divide(tree,ni,ctx);
      }break;
      case ExprType::Assignment: 
      {
        return assignment(tree,ni,ctx);
      }break;
      case ExprType::FunctionCall: 
      {
        return call(tree,ni,ctx);
      }break;
      default: 
      {
        throw std::runtime_error("Unknown expression type!");
      }
    }
  }
  
  Var evalExpressionTree(const ExprTree &tree, Context &ctx){
    return evalExpression(tree, tree.getRoot(),ctx);
  }
} /* end of namespace calc */
#endif // EVAL_H
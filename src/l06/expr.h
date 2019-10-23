#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <memory>

namespace calc{

  enum class ExprType{
    NilLiteral,
    BlnLiteral,
    IntLiteral,
    DblLiteral,
    StrLiteral,
    Symbol,
    Identity,
    Negate,
    Add,
    Subtract,
    Multiply,
    Divide,
    Assignment,
    FunctionDef,
    FunctionCall,
    Unexpected,
  };
  
  std::ostream& operator<<(std::ostream& os, const calc::ExprType& ty) {
    static const char* const ExprTypeNames[]{
      "NilLiteral",
      "BlnLiteral",
      "IntLiteral",
      "DblLiteral",
      "StrLiteral",
      "Symbol",
      "Identity",
      "Negate",
      "Add",
      "Subtract",
      "Multiply",
      "Divide",
      "Assignment",
      "FunctionDef",
      "FunctionCall",
      "Unexpected",
    };
    return os << ExprTypeNames[static_cast<int>(ty)];
  }
  
  using ExprNodeIdx = size_t;
  
  const ExprNodeIdx ExprNodeIdx_Null = 0;
  
  class ExprTree;

  class ExprNode
  {
  public:
    ExprNode(ExprType vtyp, std::string vraw)
              :
              parent(ExprNodeIdx_Null),self(ExprNodeIdx_Null),typ(vtyp),raw(vraw){}
    
    ExprNode(ExprNodeIdx vparent, ExprNodeIdx vself, ExprType vtyp, std::string vraw)
              :
              parent(vparent),self(vself),typ(vtyp),raw(vraw){}
      
  private:
    ExprNodeIdx parent;
    
    ExprNodeIdx self;
    
    ExprType typ;
    
    std::vector<ExprNodeIdx> children;
    
    std::string raw;
    
    friend class ExprTree;
  };

  class ExprTree {
  public:
  
    ExprTree(ExprType rootType, std::string s){
      nodes.push_back(ExprNode(rootType,s));
    }
    
    ExprNodeIdx getRoot() const ;
    
    ExprType getExprType(ExprNodeIdx) const ;
    
    std::string getRaw(ExprNodeIdx) const ;
    
    size_t getChildCount(ExprNodeIdx) const ;
    
    ExprNodeIdx getChildAt(ExprNodeIdx, size_t) const ;
    
    ExprTree copySubtree(ExprNodeIdx subtreeRootIdx) ;
    
    ExprNodeIdx add(ExprNodeIdx parentI,ExprType typ,std::string s) ;
    
  private:
    void copyChildNodes(ExprNodeIdx,ExprNodeIdx, ExprTree&) const;
    
    std::vector<ExprNode> nodes;
  };
  
  void ExprTree::copyChildNodes(ExprNodeIdx fromParentNode,ExprNodeIdx toParentNode, ExprTree &other) const{
    ExprNodeIdx fromChildNode;
    ExprNodeIdx toChildNode;
    for(size_t ci = 0; ci < getChildCount(fromParentNode); ++ci){
      fromChildNode = getChildAt(fromParentNode,ci);
      toChildNode = other.add(toParentNode,getExprType(fromChildNode),getRaw(fromChildNode));
      copyChildNodes(fromChildNode,toChildNode,other);
    };
    
  }
  
  ExprNodeIdx ExprTree::getRoot() const
  {
    return 0;
  }
  
  ExprType ExprTree::getExprType(ExprNodeIdx i) const
  {
    return nodes.at(i).typ;
  }
  
  std::string ExprTree::getRaw(ExprNodeIdx i) const
  {
    return nodes.at(i).raw;
  }
  
  size_t ExprTree::getChildCount(ExprNodeIdx i) const
  {
    return nodes.at(i).children.size();
  }
    
  ExprNodeIdx ExprTree::getChildAt(ExprNodeIdx i, size_t childi) const
  {
    return nodes.at(i).children.at(childi);
  }
  
  ExprTree ExprTree::copySubtree(ExprNodeIdx fromRoot)
  {
    ExprTree tree(getExprType(fromRoot),getRaw(fromRoot));
    copyChildNodes(fromRoot,tree.getRoot(),tree);
    return tree;
  }
  
  ExprNodeIdx ExprTree::add(ExprNodeIdx parent,ExprType typ,std::string s)
  {
    ExprNodeIdx newn =  nodes.size();
    nodes.push_back(ExprNode(parent,newn, typ, s));
    nodes.at(parent).children.push_back(newn);
    return newn;
  }
} /* end of namespace calc */
#endif // EXPR_H
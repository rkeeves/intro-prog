#ifndef RAWPTRTREE_H
#define RAWPTRTREE_H

#include <stack>

#include "lzw.h"

namespace lzw{
  /**
   * RawPtrNode
   *
   * A simple node for binary tree.
   *
   */
  template<typename T>
  class RawPtrNode
  {
  // LIFECYCLE
  public:
    
    RawPtrNode (T val) : v(val), l(nullptr), r(nullptr) { };
    
    ~RawPtrNode (){  };
    
  private:
  
    RawPtrNode (const RawPtrNode &);
    
    RawPtrNode & operator= (const RawPtrNode &);
    
  // PUBLIC FUNCS
  public:
    RawPtrNode<T>* getChild(bool isRight) const
    { 
      return isRight ? r : l;
    }
    
    void setChild(bool isRight, RawPtrNode<T> *newn)
    { 
      if(isRight){
        r = newn;
      }else{
        l = newn;
      };
    };
    
    void setVal(T newv){ v = newv;}
    
    T getVal() const { return v;}
    
  // PRIVATE FUNCS
  private:
    
  // PRIVATE FIELDS
  private:
  
    T v;

    RawPtrNode<T>* l;
    
    RawPtrNode<T> *r;
  };
  
  /**
   * RawPtrTreeIteratorImpl
   *
   * Iterator for traversing and also for growing the tree.
   *
   */
  class RawPtrTreeIteratorImpl : public LZWBTreeGrower<char>{
    
  // LIFECYCLE
  public:
    RawPtrTreeIteratorImpl(RawPtrNode<char>* theroot) : root(theroot), cur(root){};
    
    ~RawPtrTreeIteratorImpl(){};
    
  private:
  
    RawPtrTreeIteratorImpl (const RawPtrTreeIteratorImpl &);
    
    RawPtrTreeIteratorImpl & operator= (const RawPtrTreeIteratorImpl &);
    
  // PUBLIC FUNCS
  public:
  
    virtual void pushState() override
    {
      st.push(cur);
    }
    
    virtual void popState() override
    {
      cur = st.top();
      st.pop();
    }
    
    virtual char getVal() const override
    {
      return cur->getVal();
    }
    
    virtual bool hasChild(bool isRight) const override
    {
      return (cur->getChild(isRight) != NULL);
    }
    
    virtual void toChild(bool toRight) override
    {
      cur = cur->getChild(toRight);
    }
    
    virtual void backToRoot() override 
    {
      cur=root;
    }
    
    virtual void growChild(bool toRight, char v) override 
    {
      cur->setChild(toRight,new RawPtrNode<char>(v));
    }
    
  // PRIVATE FUNCS
  private:
  
  //PRIVATE FIELDS
  private:
    std::stack<RawPtrNode<char>*> st;
    
    RawPtrNode<char>* root;
    
    RawPtrNode<char>* cur;
  };
  
  /**
   * RawPtrTree
   *
   * A simple binary tree.
   *
   */
  class RawPtrTree : public LZWBTree{
  // LIFECYCLE
  public:
  
    RawPtrTree() : root(new RawPtrNode<char>('/')), grower(root){ };

    ~RawPtrTree()
    {
      freeNode(root);
    };
    
  private:
  
    RawPtrTree (const RawPtrTree &);
    
    RawPtrTree & operator= (const RawPtrTree &);
    
  // PUBLIC FUNC
  public:
  
    virtual void operator<< (char b) override
    {
      if (b == '0'){
        push(false, b);
      }else{
        push(true, b);
      }
    }
    
    virtual void preOrder(bool rightToLeft, TreeVisitor* visitor) const override
    {
      PreOrderTraverser tr(this);
      tr.traverse(rightToLeft,visitor);
    }
    
    virtual void inOrder(bool rightToLeft, TreeVisitor* visitor) const override
    {
      InOrderTraverser tr(this);
      tr.traverse(rightToLeft,visitor);
    }
    
    virtual void postOrder(bool rightToLeft, TreeVisitor* visitor) const override
    {
      PostOrderTraverser tr(this);
      tr.traverse(rightToLeft,visitor);
    }
    
    virtual LZWBTreeIterator<char>* newIterator() const override
    {
      return new RawPtrTreeIteratorImpl(this->getRoot());
    }
    
  // PRIVATE FUNC
  private:
  
    void push(bool toRight, char v)
    {
      if (grower.hasChild(toRight)){
          grower.toChild(toRight);
      }else{
          grower.growChild(toRight,v);
          grower.backToRoot();
      }
    }
    
    RawPtrNode<char> *const getRoot() const
    {
      return root;
    }
    
    void freeNode(RawPtrNode<char>* n)
    {
      if (n != NULL)
      {
          freeNode (n->getChild(true));
          freeNode (n->getChild(false));
          delete n;
      }
    }
    
  // PRIVATE FIELDS
  private:

    RawPtrNode<char>* root;
    
    RawPtrTreeIteratorImpl grower;
    
    friend class RawPtrTreeIteratorImpl;
  };
} /* end of namespace lzw */
#endif // RAWPTRTREE_H
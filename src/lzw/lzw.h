#ifndef LZW_H
#define LZW_H

namespace lzw{
  
  /**
   * LZWBTreeIterator
   *
   * Interface for tree iterators used in traversing trees.
   *
   */
  template<typename T>
  class LZWBTreeIterator{
    
  // LIFECYCLE
  public:
  
    ~LZWBTreeIterator(){};
    
  // PUBLIC FUNCS
  public:
  
    virtual void pushState() = 0;
    
    virtual void popState() = 0;
  
    virtual T getVal() const = 0;
    
    virtual bool hasChild(bool isRight) const = 0;
    
    virtual void toChild(bool toRight) = 0;
  };
  
  
  /**
   * LZWBTreeGrower
   *
   * Interface for tree growers used in growing trees.
   *
   */
  template<typename T>
  class LZWBTreeGrower : public LZWBTreeIterator<T>{
    
  // LIFECYCLE
  public:
  
    ~LZWBTreeGrower(){};
    
  // PUBLIC FUNCS
  public:
  
    virtual void backToRoot() = 0;
    
    virtual void growChild(bool toRight, T v) = 0;
  };
  
  
  /**
   * TreeVisitor
   *
   * Interface for classes, who define behavior during visiting tree nodes.
   * This interface is used by tree traversers.
   *
   */
  class TreeVisitor{
  
  // LIFECYCLE
  public:
    virtual ~TreeVisitor(){};
  
  // PUBLIC FUNCS
  public:
    virtual void onStart(){}
    
    virtual void onEnd(){}

    virtual void onNode(char v, bool leftExists, bool rightExists) {}
    
    virtual void onDownToChild(bool isRightChild) {}
    
    virtual void onUpFromChild(bool isRightChild) {}
    
  };
  
  
  /**
   * LZWBTree
   *
   * Interface for all lzw btree implementations.
   *
   */
  class LZWBTree{
    
  // LIFECYCLE
  public:
    virtual ~LZWBTree(){};
    
  // PUBLIC FUNCS
  public:
    
    virtual void operator<< (char b) = 0;
    
    virtual LZWBTreeIterator<char> *newIterator() const = 0;
    
    virtual void preOrder(bool rightToLeft, TreeVisitor* visitor) const = 0;
    
    virtual void inOrder(bool rightToLeft, TreeVisitor* visitor) const = 0;
    
    virtual void postOrder(bool rightToLeft, TreeVisitor* visitor) const = 0;
    
  };
  
  /**
   * Traverser
   *
   * Abstract class for pre-, in- and postorder traversal strategies.
   *
   */
  class Traverser{
    
  // LIFECYCLE
  public:
    Traverser(const LZWBTree *const thetree) :  tree(thetree), it(NULL), rl(false), visitor(NULL){};
    
    virtual ~Traverser(){ if(it != NULL) delete it; };
  
  private:
  
    Traverser (const Traverser &);
    
    Traverser & operator= (const Traverser &);
    
  // PUBLIC FUNCS
  public:
    int traverse(bool visitRightChildFirst, TreeVisitor* visitor){
      if(tree != NULL && visitor != NULL){
        this->visitor = visitor;
        this->it = tree->newIterator();
        this->rl = visitRightChildFirst;
        visitor->onStart();
        visitNode();
        visitor->onEnd();
        if(it != NULL){
          delete it;
          it = NULL;
        } 
        visitor = NULL;
        return 0;
      }
      return -1;
    };
  // PROTECTED FUNCS
  protected:
  
    virtual void visitNode() = 0;
    
    void visitFirstChild(){
      visitChild(rl);
    }
    
    void visitSecondChild(){
      visitChild(!rl);
    }
    
    void processCurrent(){
      visitor->onNode(it->getVal(),it->hasChild(false),it->hasChild(true));
    }
  
  // PRIVATE FUNCS
  private:
  
    void visitChild(bool shouldTryRightChild){
      if(it->hasChild(shouldTryRightChild)){
        it->pushState();
        visitor->onDownToChild(shouldTryRightChild);
        it->toChild(shouldTryRightChild);
        visitNode();
        it->popState();
        visitor->onUpFromChild(shouldTryRightChild);
      }
    }
    
  // PRIVATE FIELDS
  private:

    bool rl = false;
    
    const LZWBTree *const tree;
    
    LZWBTreeIterator<char>* it;
    
    TreeVisitor* visitor;
  };
  
  
  /**
   * PreOrderTraverser
   *
   * Impl class for preorder traversal.
   *
   */
  class PreOrderTraverser : public Traverser{
    
  // LIFECYCLE
  public:
  
    PreOrderTraverser(const LZWBTree *const thetree) : Traverser(thetree){};
    
    virtual ~PreOrderTraverser(){};
    
  private:
  
    PreOrderTraverser (const PreOrderTraverser &);
    
    PreOrderTraverser & operator= (const PreOrderTraverser &);
    
  // PROTECTED FUNCS
  protected:
  
    virtual void visitNode() override{
      processCurrent();
      visitFirstChild();
      visitSecondChild();
    }
  };
  
  
  /**
   * InOrderTraverser
   *
   * Impl class for inorder traversal.
   *
   */
  class InOrderTraverser : public Traverser{
    
  // LIFECYCLE
  public:
  
    InOrderTraverser(const LZWBTree *const thetree) : Traverser(thetree){};
    
    virtual ~InOrderTraverser(){};
    
  private:
  
    InOrderTraverser (const InOrderTraverser &);
    
    InOrderTraverser & operator= (const InOrderTraverser &);
  // PROTECTED FUNCS
  protected:
  
    virtual void visitNode() override{
      visitFirstChild();
      processCurrent();
      visitSecondChild();
    }
  };
  
  
  /**
   * PostOrderTraverser
   *
   * Impl class for postorder traversal.
   *
   */
  class PostOrderTraverser : public Traverser{
  
  // LIFECYCLE
  public:
  
    PostOrderTraverser(const LZWBTree *const thetree) : Traverser(thetree){};
    
    virtual ~PostOrderTraverser(){};
    
  private:
  
    PostOrderTraverser (const PostOrderTraverser &);
    
    PostOrderTraverser & operator= (const PostOrderTraverser &);
    
  // PROTECTED FUNCS
  protected:
  
    virtual void visitNode() override{
      visitFirstChild();
      visitSecondChild();
      processCurrent();
    }
  };
} /* end of namespace lzw */
#endif // LZW_H
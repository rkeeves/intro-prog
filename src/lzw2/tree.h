#ifndef TREE_H
#define TREE_H

#include <stack>  // pre, in postorder traversal state keepinf
#include <exception> // for iterator exceptions

namespace lzw{

// Forward decl for friend classing with Node
template <class T> class NodeFactory;

template <class T> class Accessor;


/**
 *
 * Node
 *
 * Represents a node in a binary tree.
 * Use of shared_ptr gave a large overhead.
 * Node's cleanup and instation is done via NodeFactory
 */
template<typename T>
class Node{
// Lifecycle
private:
  
  Node(T val) : v(val), l(nullptr), r(nullptr) { };
  
  ~Node (){ };
  
  Node (const Node<T> &);
  
  Node & operator= (const Node<T> &);
// Lifecycle end
private:

  T v;
  
  Node<T>* l;
  
  Node<T>* r;
  
  friend class NodeFactory<T>;
  
  friend class Accessor<T>;
};

/**
 *
 * NodeFactory
 *
 * Tree does not instantiate or delete nodes directly.
 * Instantiation and destroy/cleanup is delegated to NodeFactory.
 */
template<typename T>
class NodeFactory{
// Lifecycle - Stateless
// Lifecycle end
public:
  
  Node<T> *construct(T v)
  {
    return new Node<T>(v);
  }
  
  void destroy(Node<T> *n)
  {
    if (n != nullptr){
        destroy (n->l);
        destroy (n->r);
        delete n;
        n = nullptr;
    }
  }
  
  Node<T> * addChild(Node<T> *const parent, bool right, T v)
  {
    if(right){
      destroy(parent->r);
      parent->r = construct(v);
      return parent->r;
    }else{
      destroy(parent->l);
      parent->l = construct(v);
      return parent->l;
    }
  }
  
};

/**
 *
 * Accessor
 *
 */
template<typename T>
class Accessor{
// Lifecycle
public:
  
  Accessor() : pcur(nullptr) { }
  
  Accessor(Node<T> *ptr) : pcur(ptr) { }
  
  Accessor (const Accessor<T> &o) : pcur(o.pcur) { }
  
  Accessor & operator= (const Accessor<T> &o){
    this->pcur=o.pcur;
    return *this;
  }
  
  ~Accessor (){ };
// Lifecycle end
public:
  
  bool operator==(const Accessor<T>& o) const
  {
    return (this->pcur == o.pcur);
  }
      
  Node<T> * get() const
  {
    return pcur;
  }
  
  void set(Node<T> * ptr)
  {
    pcur = ptr;
  }
  
  inline bool isNull() const
  {
    return (pcur==nullptr);        
  }
  
  inline T getValue() const
  {
    if(isNull()){ throw std::runtime_error("Tried to access value of null node");}
    return pcur->v;
  }
  
  inline bool hasChild(bool right) const
  {
    if(pcur == nullptr){ return false;}
    if(right){
      return (pcur->r != nullptr);
    }else{
      return (pcur->l != nullptr);
    }
  }     
  
  inline bool hasLeft() const
  {
    return hasChild(false);
  }
  
  inline bool hasRight() const
  {
    return hasChild(true);
  }
  
  inline bool isLeaf() const
  {
    return !(hasLeft() || hasRight());
  }
  
  Node<T>* getChild(bool right) const
  {
    if(isNull()){ throw std::runtime_error("Tried to access child of null node");}
    if(right){
      return pcur->r;
    }else{
      return pcur->l;
    }
  }
  
  inline bool getRight() const {
    return getChild(true);
  }
  
  inline bool getLeft() const{
    return getChild(false);
  }
  
  inline bool isParentOf(bool right, Node<T>*child) const
  {
    if(pcur == nullptr){ return false;}
    if(right){
      return (pcur->r == child);
    }else{
      return (pcur->l == child);
    }
  }
  
  inline bool isChildOf(bool right, Node<T>*parent) const
  {
    if(pcur == nullptr){ return false;}
    if(right){
      return (parent->r == pcur);
    }else{
      return (parent->l == pcur);
    }
  }
  
protected:
  
  Node<T> *pcur;
};
// TODO do composition instead of inheritance.
// BaseIterator becomes IteratorState
// All iterators will jsut call this shit...
/**
 *
 * BaseIterator
 *
 */
template<typename T>
class BaseIterator{
  
// Lifecycle
public:
  BaseIterator(bool arg_rightFirst, Accessor<T> accessor) :  acsr(accessor), rightFirst(arg_rightFirst){};
  
  virtual ~BaseIterator(){ };

private:

  BaseIterator (const BaseIterator<T> &);
  
  BaseIterator & operator= (const BaseIterator<T> &);
// Lifecycle end
public:
  
  virtual void next() = 0;
  
  inline T getValue() const
  {
    return acsr.getValue();
  }
        
  inline bool isNull() const
  {
    return acsr.isNull();
  }
  
  bool hasFirst() const
  { 
    return acsr.hasChild(rightFirst); 
  }
  
  bool hasSecond() const
  { 
    return acsr.hasChild(!rightFirst); 
  }
  
  
protected:

  virtual void init() = 0; 
  
  void toLastState()
  {
    if(st.empty()){
      acsr.set(nullptr);
    }else{
      acsr.set(st.top());
      st.pop();
    }
  }
  
  Node<T>* getFirst()
  {
    return acsr.getChild(rightFirst);
  }
  
  Node<T>* getSecond()
  {
   return  acsr.getChild(!rightFirst);
  }
  
  void toFirst()
  {
    acsr.set(getFirst());
  }
  
  void toSecond()
  {
    acsr.set(getSecond());
  }
  
protected:

  std::stack<Node<T>*> st;
  
  Accessor<T> acsr;
  
  bool rightFirst;
};

// Forward decl for friend classing with Iterator implementations
// This is necessary due to the fact that initialization is required.
// Example: In Inorder case you have to travel down the leftmost branch.
template <class T> class Tree;

/**
 *
 * InorderIterator
 *
 */
template<typename T>
class InorderIterator : public BaseIterator<T>{
// Lifecycle
public:

  InorderIterator(bool arg_rightFirst, Accessor<T> accessor) :  BaseIterator<T>(arg_rightFirst,accessor){}
  
  virtual ~InorderIterator(){ };
  
  InorderIterator (const InorderIterator<T> &o) : BaseIterator<T>(o.rightFirst,o.acsr) {};
  
  InorderIterator & operator= (const InorderIterator<T> &o){
    this->rightFirst = o.rightFirst;
    this->acsr = o.acsr;
  }
  
private:
// Lifecycle end

public:

  virtual void next() override
  {
    if(this->isNull()){ return; }
    if(this->hasSecond()) {
        this->toSecond();
        followFirstBranch();
        return;
    }
    this->toLastState();
  };
  
    
  InorderIterator<T>& operator ++ () 
  {
      next(); 
      return *this; 
  } 
  
  InorderIterator<T> operator ++ (int) {
    InorderIterator<T> temp = *this;
    ++*this;
    return temp;
  }
  
  inline bool equals(const InorderIterator<T>&o) const{
    return ((o.rightFirst == this->rightFirst) && (o.acsr == this->acsr) && (o.st == this->st) );
  }
  
  bool operator==(const InorderIterator<T>&o) const{
    return this->equals(o);
  }
  
  bool operator!=(const InorderIterator<T>&o) const{
    return !(this->equals(o));
  }
  
protected:
  virtual void init() override 
  {
    followFirstBranch();
  }
  
private:

  void followFirstBranch() 
  {
    if(this->isNull()){ return;}
    while(this->hasFirst()){
      this->st.push(this->acsr.get());
      this->toFirst();
    }
  }
  
  friend class Tree<T>;
};

/**
 *
 * PreorderIterator
 *
 */
template<typename T>
class PreorderIterator : public BaseIterator<T>{
// Lifecycle
public:

  PreorderIterator(bool arg_rightFirst, Accessor<T> accessor) :  BaseIterator<T>(arg_rightFirst,accessor){}
  
  virtual ~PreorderIterator(){ };
  
  PreorderIterator (const PreorderIterator<T> &o) : BaseIterator<T>(o.rightFirst,o.acsr) {};
  
  PreorderIterator & operator= (const PreorderIterator<T> &o){
    this->rightFirst = o.rightFirst;
    this->acsr = o.acsr;
  }

private:
// Lifecycle end 
  
public:

  virtual void next() override
  { 
    if(this->isNull()){ return; }
    this->toLastState();
    if(this->hasSecond()) {
      this->st.push(this->getSecond());
    }
    if(this->hasFirst()) {
      this->st.push(this->getFirst());
    }
  };
  
    
  PreorderIterator<T>& operator ++ () 
  {
      next(); 
      return *this; 
  } 
  
  PreorderIterator<T> operator ++ (int) {
    PreorderIterator<T> temp = *this;
    ++*this;
    return temp;
  }
  
  inline bool equals(const PreorderIterator<T>&o) const{
    return ((o.rightFirst == this->rightFirst) && (o.acsr == this->acsr) && (o.st == this->st) );
  }
  
  bool operator==(const PreorderIterator<T>&o) const{
    return this->equals(o);
  }
  
  bool operator!=(const PreorderIterator<T>&o) const{
    return !(this->equals(o));
  }
  
protected:

  virtual void init() override 
  {
    this->st.push(this->acsr.get());
    next();
  }
  
private:
  
  friend class Tree<T>;
};


/**
 *
 * PostorderIterator
 *
 */
 
template<typename T>
class PostorderIterator : public BaseIterator<T>{
// Lifecycle
public:

  PostorderIterator(bool arg_rightFirst, Accessor<T> accessor) :  BaseIterator<T>(arg_rightFirst,accessor){}
  
  virtual ~PostorderIterator(){ };
  
  PostorderIterator (const PostorderIterator<T> &o) : BaseIterator<T>(o.rightFirst,o.acsr) {};
  
  PostorderIterator & operator= (const PostorderIterator<T> &o){
    this->rightFirst = o.rightFirst;
    this->acsr = o.acsr;
  }

private:
// Lifecycle end 
  
public:

  virtual void next() override
  {
    this->toLastState();
    auto current = this->acsr;
    if (! (this->st.empty()) ) {
      this->acsr.set(this->st.top());
      
      if (this->acsr.isParentOf(this->rightFirst,current.get())) {
        this->toSecond();
        findNext();
      }
     }
     this->acsr = current;
  };
  
    
  PostorderIterator<T>& operator ++ () 
  {
      next(); 
      return *this; 
  } 
  
  PostorderIterator<T> operator ++ (int) {
    PostorderIterator<T> temp = *this;
    ++*this;
    return temp;
  }
  
  inline bool equals(const PostorderIterator<T>&o) const{
    return ((o.rightFirst == this->rightFirst) && (o.acsr == this->acsr) && (o.st == this->st) );
  }
  
  bool operator==(const PostorderIterator<T>&o) const{
    return this->equals(o);
  }
  
  bool operator!=(const PostorderIterator<T>&o) const{
    return !(this->equals(o));
  }

protected:

  virtual void init() override 
  {
    findNext();
    next();
  }
  
private:

  void findNext() {
    while( ! this->isNull()){
      this->st.push(this->acsr.get());
      if (this->hasFirst()) {  
        this->toFirst();
      } else {  
        this->toSecond();
      }
    }
  }

  friend class Tree<T>;
};

/**
 *
 * Tree
 *
 */
template <class T>
class Tree {
// Lifecycle
public:

  Tree(T v) : root(factory.construct(v)){}

  ~Tree(){factory.destroy(root);}
  
private:

  Tree(const Tree&);
  
  Tree& operator=(const Tree&);
  
// Lifecycle end
public:

  Accessor<T> accessor_root()
  {
    return Accessor<T>(root);
  }
  
  Accessor<T> insert(const Accessor<T>& parent, bool right, T v)
  {
    if(parent.isNull()){throw std::runtime_error("Node insertion parent was null");}
    if(parent.hasChild(right)){throw std::runtime_error("Node insertion child already exists");}
    return Accessor<T>(factory.addChild(parent.get(),right,v));
  }
  
  InorderIterator<T> begin_inorder_left()
  {
    InorderIterator<T> it(false,accessor_root());
    it.init();
    return it;
  }
  
  InorderIterator<T> end_inorder_left()
  {
    return InorderIterator<T>(false,Accessor<T>(nullptr));
  }
  
  InorderIterator<T> begin_inorder_right()
  {
    InorderIterator<T> it(true,accessor_root());
    it.init();
    return it;
  }
  
  InorderIterator<T> end_inorder_right()
  {
    return InorderIterator<T>(true,Accessor<T>(nullptr));
  }
  
  PreorderIterator<T> begin_preorder_left()
  {
    PreorderIterator<T> it(false,accessor_root());
    it.init();
    return it;
  }
  
  PreorderIterator<T> end_preorder_left()
  {
    return PreorderIterator<T>(false,Accessor<T>(nullptr));
  }
  
  PreorderIterator<T> begin_preorder_right()
  {
    PreorderIterator<T> it(true,accessor_root());
    it.init();
    return it;
  }
  
  PreorderIterator<T> end_preorder_right()
  {
    return PreorderIterator<T>(true,Accessor<T>(nullptr));
  }

  PostorderIterator<T> begin_postorder_left()
  {
    PostorderIterator<T> it(false,accessor_root());
    it.init();
    return it;
  }
  
  PostorderIterator<T> end_postorder_left()
  {
    return PostorderIterator<T>(false,Accessor<T>(nullptr));
  }
  
  PostorderIterator<T> begin_postorder_right()
  {
    PostorderIterator<T> it(true,accessor_root());
    it.init();
    return it;
  }
  
  PostorderIterator<T> end_postorder_right()
  {
    return PostorderIterator<T>(true,Accessor<T>(nullptr));
  }

protected:
  
  Node<T>* root;
  
private:

  NodeFactory<T> factory;
};

} /* end of namespace lzw */
#endif // TREE_H
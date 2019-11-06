#ifndef TREE_H
#define TREE_H

#include <bitset>	

namespace lzw{
  // SUBTREE_NODE_COUNT = 2 ^ n - 2, where n is the SubTree's max height
  // We subtract 2 because:
  //  - In a btree we can have 2 ^ n -1 nodes, like:
  //      1
  //    2  3
  //  - root always exists, we dont need to store its state, therefore we subtract 1 more
  //  
  const std::size_t SUBTREE_NODE_COUNT = 62; 
  
  using Sz_t = std::size_t;
  
  using Idx = std::size_t;
  
  using Bits = std::bitset<SUBTREE_NODE_COUNT>;
  
  inline Idx getChildIdx(Idx parent, bool right){
    return (right) ? ((2*parent)+2) : ((2*parent)+1);
  }

  inline Idx getParentIdx(Idx child){
    return (child == 0) ? child : ((child-1) / 2);
  }

class Subtree{
    // Lifecycle
public:
    Subtree () { };
    
    ~Subtree(){};
    
private:
  Subtree (const Subtree &);
  
  Subtree & operator= (const Subtree &);

// Lifecycle end
public:
  class Node{
    
  public:
  
    Node(Idx position, Subtree* thetree) : pos(position), tree(thetree){ }
    
    ~Node(){}
    
    Node (const Node &o) : pos(o.pos), tree(o.tree) {}
  
    Node & operator= (const Node &o){
      pos = o.pos;
      tree = o.tree;
      return *this;
    }
  public:
    
    inline Node getChild(bool right){
      return Node(getChildIdx(pos,right),tree);
    }
    
    inline void toChild(bool right){
      pos = getChildIdx(pos,right);
    }
    
    inline void toParent(){
      pos = getParentIdx(pos);
    }
    
    inline bool isRoot() const{
      return (pos == 0);
    }
    
    inline bool isLeft() const{
      return (pos % 2);
    }
    
    inline bool isRight() const{
      return !isLeft();
    }
    
    inline bool hasChild(bool right) const{
      return tree->hasChild(pos,right);
    }
    
    inline bool hasParent() const{
      return tree->hasParent(pos);
    }
    
    inline Idx getPos() const{
      return pos;
    }
    
    inline void setPos(Idx newpos){
      pos = newpos;
    }
    
    inline char to_char() const {
      if(isRoot()){
        return '/';
      }else if(isLeft()){
        return '0';
      }else{
        return '1';
      }
    }
    
  private:
    Idx pos;
      
    Subtree* tree;
  };
  
public:
  
  bool hasParent(Idx child) const
  {
    return bits.test(getParentIdx(child)-1);
  }
  
  bool hasChild(Idx parent,bool right) const
  {
    return bits.test(getChildIdx(parent,right)-1);
  }
  
  Node insert(const Node &n, bool right)
  { 
    Node nn(getChildIdx(n.getPos(),right),this);
    bits.set(nn.getPos()-1,true);
    return nn;
  }

  
  Node root_node(){
    return Node(0,this);
  }
  
  std::string to_string(){
    return bits.to_string();
  }
private:

  Bits bits;

};

class InputIterator {
// Lifecycle
public:
  InputIterator (Subtree *thetree) : tree(thetree), n(thetree->root_node()){ }
    
  ~InputIterator (){};

  InputIterator (const InputIterator &o) : tree(o.tree), n(o.n){ }
  
  InputIterator & operator= (const InputIterator &o){
    this->n = o.n;
    this->tree = o.tree;
    return *this;
  }
// Lifecycle end

public:

  void operator<< (char b)
  { 
    bool toRight = (b != '0');
    if (n.hasChild(toRight)){
      n.setPos(getChildIdx(n.getPos(),toRight));
    }else{
      tree->insert(n,toRight);
      n = tree->root_node();
    }
  }

private:
  Subtree::Node n;
  
  Subtree *tree;
};
} /* end of namespace lzw */
#endif // TREE_H
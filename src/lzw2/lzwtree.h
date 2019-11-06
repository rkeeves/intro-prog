#ifndef LZWTREE_H
#define LZWTREE_H

#include "tree.h"

namespace lzw{


/**
 * LzwTree
 * Example:
 *
 *         /
 *    0         2
 * 0         0    3
 *
 * ORDER        LEFT_FIRST  RIGHT_FIRST
 * Inorder      00/023      320/00
 * Preorder     /00203      /23000
 * Postorder    00032/      30200/
 */
class LzwTree : public Tree<char> {
// Lifecycle
public:
    LzwTree () : Tree<char>('/'){ };
    
    ~LzwTree (){};
    
private:
  LzwTree (const LzwTree &);
  
  LzwTree & operator= (const LzwTree &);
// Lifecycle end

public:
     
  /**
   * InputIterator
   *
   */
  class InputIterator {
  // Lifecycle
  public:
    InputIterator (LzwTree &thetree) : tree(thetree), acsr(thetree.accessor_root()){ }
      
    ~InputIterator (){};

    InputIterator (const InputIterator &o) : tree(o.tree), acsr(o.acsr){ }
    
    InputIterator & operator= (const InputIterator &o){
      acsr = o.acsr;
      tree = o.tree;
      return *this;
    }
  // Lifecycle end

  public:

    void operator<< (char b)
    { 
      bool toRight = (b != '0');
      if (acsr.hasChild(toRight)){
        acsr.set(acsr.getChild(toRight));
      }else{
        tree.insert(acsr,toRight,b);
        acsr = tree.accessor_root();
      }
    }

  private:
    Accessor<char> acsr;
    
    LzwTree &tree;
  };
public:
  InputIterator begin_input_iterator(){
    return InputIterator(*this);
  }
private:

};
} /* end of namespace lzw */
#endif // LZWTREE_H
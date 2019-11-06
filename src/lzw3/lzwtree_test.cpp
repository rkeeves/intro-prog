#include "tree.h"

#include <iostream>
#include <stack>

/**
 * CAUTION!
 * 
 * Currently only a subtree is functional it has size constraints.
 * 
 * (Worst case scenario would be an uncaught std::out_of_range originating from the underlying bitset if you try to access
 * an index which is larger than the bitset was templated for (size is a template param), but still...)
 *
 * The general idea is to link these subtrees instead of RawNodes thereby decreasing footprint.
 * This will also speed up the process by less interaction with RAM is needed.
 * In the RawNode case each node resides in memory and has a decent footprint.
 * In this case these subtrees are essentially chunks whoch can be connected via ptrs.
 * This is currently not implemented.
 * Full subtrees can also be replaced with proxies. Aka theres no need to store the bits of a subtree if they are all 1.
 * The subtrees can be linked together via ptrs or something else.
 * Im not sure whether the links (e.g. ptrs) should be the part of the subtree class?
 * I mean we can use chain of responsibility pattern and handle the redirects via other classes.
 */

using namespace lzw;

void traverse_inorder(Subtree::Node n, int height){
  if(n.hasChild(false))
    traverse_inorder(n.getChild(false),height+1); 
  std::cout << std::string(3*height,'-')<< n.to_char() << "("<< height-1<<")" << std::endl;
  if(n.hasChild(true))
    traverse_inorder(n.getChild(true),height+1); 
}

class RawNode{
  char c;
  RawNode* l;
  RawNode* r;
};

int main(int argc, char** argv){
  Subtree tree;
  auto root = tree.root_node();
  {
    InputIterator inp(&tree);
    std::string ins = "01111001001001000111"; // This is a totally ad hoc 0 1 sequence for 'test'
    for(size_t i = 0; i < ins.size(); ++i){inp << ins[i];}
    
  }
  traverse_inorder(root,1);
  std::cout << "Bits [" << tree.to_string() << "]" << std::endl;
  std::cout << "Full footprint " << (sizeof(Subtree) + (SUBTREE_NODE_COUNT+2) * sizeof(Subtree*)) << " bytes" <<std::endl;
  std::cout << "RawNode footprint " << ((SUBTREE_NODE_COUNT+1) * sizeof(RawNode)) << " bytes " << std::endl;
  return 0;
}



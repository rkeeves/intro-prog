#include <iostream>
#include <sstream>

#include "lzwtree.h"

using namespace lzw;

void test1(){
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
  LzwTree tree;
  auto inpit = tree.begin_input_iterator();
   inpit << '0';
   inpit << '0';
   inpit << '0';
   inpit << '2';
   inpit << '2';
   inpit << '0';
   inpit << '2';
   inpit << '3';
   
  { std::stringstream ss;
    for(auto it = tree.begin_inorder_left(); it != tree.end_inorder_left(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("00/023")!=0){
      throw std::runtime_error(std::string("Inorder left fail ") + ss.str());
    }
  }
  {
    std::stringstream ss;
    for(auto it = tree.begin_inorder_right(); it != tree.end_inorder_right(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("320/00")!=0){
      throw std::runtime_error(std::string("Inorder right fail ") + ss.str());
    }
  }
  { 
    std::stringstream ss;
    for(auto it = tree.begin_preorder_left(); it != tree.end_preorder_left(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("/00203")!=0){
      throw std::runtime_error(std::string("Preorder left fail ")  + ss.str());
    }
  }
  { 
    std::stringstream ss;
    for(auto it = tree.begin_preorder_right(); it != tree.end_preorder_right(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("/23000")!=0){
      throw std::runtime_error(std::string("Preorder right fail ")  + ss.str() );
    }
  }
  { 
    std::stringstream ss;
    for(auto it = tree.begin_postorder_left(); it != tree.end_postorder_left(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("00032/")!=0){
      throw std::runtime_error(std::string("Preorder left fail ")  + ss.str() );
    }
  }
  {
    std::stringstream ss;
    for(auto it = tree.begin_postorder_right(); it != tree.end_postorder_right(); ++it){
      ss << it.getValue();
    }
    if(ss.str().compare("30200/")!=0){
      throw std::runtime_error(std::string("Preorder right fail ")  + ss.str() );
    }
  }
}

int main(int argc, char** argv){
  try{
    test1();
    std::cout << "Test success!" << std::endl;
  }catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }catch(...){
    std::cout << "Unknown error!" << std::endl;
  }
  return 0;
}
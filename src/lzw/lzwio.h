#ifndef LZWIO_H
#define LZWIO_H

#include <iostream>	
#include <fstream>

namespace lzw{
  
  void fillFromFile(std::fstream &inFile, LZWBTree &tree,bool literalBinary, int maxbytes){
    char b;
    while (inFile.read ((char *) &b, sizeof (unsigned char))){
      if (b == 0x0a){break;}
    }
    bool inComment = false;
    int bytes = 0;
    while (inFile.read ((char *) &b, sizeof (unsigned char)))
    {
        if (b == '>'){
            inComment = true;
            continue;
        }
        if (b == '\n'){
            inComment = false;
            continue;
        }
        if (inComment || b == 'N'){
          continue;
        }
        if((maxbytes != -1) && (bytes > maxbytes) ){
          break;
        }
        if(literalBinary){
          if (b == '0'){ 
            tree << '0';
          }else{
            tree << '1';
          }
        }else{
          for (int i = 0; i < 8; ++i)
          {
              if (b & 0b10000000){ 
                tree << '1';
              }else{
                tree << '0';
              }
              b <<= 1;
          }
        }
        bytes++;
    }
  }
  
  void writeToFile(std::ostream &os, const LZWBTree &tree){
    PrettyPrinter printer(os);
    tree.inOrder(true,&printer);
    DepthAnalyzer da;
    tree.inOrder(true,&da);
    DepthVarianceAnalyzer dva(da.getMeanDepth());
    tree.inOrder(true,&dva);
    os << "depth: " << da.getMaxDepth() << std::endl;
    os << "mean: " << da.getMeanDepth() << std::endl;
    os << "var: " << dva.getDepthVariance() << std::endl;
  }
} /* end of namespace lzw */
#endif // LZWIO_H
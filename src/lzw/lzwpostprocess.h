#ifndef LZWPOSTPROCESS_H
#define LZWPOSTPROCESS_H

#include <iostream>	
#include <cmath>

#include "lzw.h"

namespace lzw{
  
  /**
   * PrettyPrinter
   *
   * Handles ONLY the pretty printing of lzw binary tree nodes.
   * This will not calculate nor print the lzw depth, mean, variation.
   *
   * Example output:
   * ---------1(2)
   * ------1(1)
   * ---------0(2)
   * ---/(0)
   * ---------1(2)
   * ------0(1)
   *
   */
  class PrettyPrinter : public TreeVisitor{
  // LIFECYCLE
  public:
  
    PrettyPrinter(std::ostream & ostr) : os(ostr), curdepth(0){}
    
    ~PrettyPrinter(){};
    
  private:
    PrettyPrinter();
    
    PrettyPrinter (const PrettyPrinter &);
    
    PrettyPrinter & operator= (const PrettyPrinter &);
    
  // PUBLIC FUNCS
  public:

    virtual void onStart() override{
      curdepth = 0;
    }
    
    virtual void onNode(char v, bool leftExists, bool rightExists) override {
      for (int i = 0; i < curdepth + 1; ++i){os  << "---";}   
      os  << v << "(" << curdepth << ")" << std::endl;
    }
    
    inline virtual void onDownToChild(bool isRightChild) override {
      curdepth++;
    }
    
    inline virtual void onUpFromChild(bool isRightChild) override {
      curdepth--;
    }
    
  // PRIVATE FUNCS
  private:
  
  // PRIVATE FIELDS
  private:
  
    int curdepth;
    
    std::ostream & os;
  };
  
  
  /**
   * DepthAnalyzer
   *
   * Handles the calculation of mean and max depth of an lzw btree.
   *
   */
  class DepthAnalyzer : public TreeVisitor{
  // LIFECYCLE
  public:
  
    DepthAnalyzer() : curdepth(0), maxdepth(0),leafCount(0), depthSum(0){}
    
    ~DepthAnalyzer(){};
    
  private:
    
    DepthAnalyzer (const DepthAnalyzer &);
    
    DepthAnalyzer & operator= (const DepthAnalyzer &);
    
  // PUBLIC FUNCS
  public:

    inline double getMeanDepth() const{ return (leafCount == 0) ? 0 : (depthSum / leafCount);};
    
    inline int getMaxDepth() const{ return maxdepth;};
    
    virtual void onStart() override{
      curdepth = 0;
      maxdepth = 0;
      leafCount = 0;
      depthSum = 0.0;
    }
    
    virtual void onNode(char v, bool leftExists, bool rightExists) override {
      if( !(leftExists || rightExists) ){
        leafCount++;
        depthSum += curdepth;
      }
    }
    
    inline virtual void onDownToChild(bool isRightChild) override {
      curdepth++;
      if(maxdepth < curdepth) maxdepth = curdepth;
    }
    
    inline virtual void onUpFromChild(bool isRightChild) override {
      curdepth--;
    }
    
  // PRIVATE FUNCS
  private:
  
  // PRIVATE FIELDS
  private:
  
    int curdepth;
    
    int maxdepth;
    
    int leafCount;
    
    double depthSum;
    
  };
  
  
  /**
   * DepthVarianceAnalyzer
   *
   * Handles the calculation of variance in leaf depths of an lzw btree.
   *
   */
  class DepthVarianceAnalyzer : public TreeVisitor{
  // LIFECYCLE
  public:
  
    DepthVarianceAnalyzer(double meanDepth) : curdepth(0), leafCount(0),varSum(0), depthMean(meanDepth){}
    
    ~DepthVarianceAnalyzer(){};
    
  private:
    DepthVarianceAnalyzer();
    
    DepthVarianceAnalyzer (const DepthVarianceAnalyzer &);
    
    DepthVarianceAnalyzer & operator= (const DepthVarianceAnalyzer &);
    
  // PUBLIC FUNCS
  public:

    inline double getDepthVariance() const{
      if (leafCount - 1 > 0)
        return std::sqrt (varSum / (leafCount - 1));
      else
        return std::sqrt (varSum);
    };
    
    virtual void onStart() override{
      curdepth = 0;
      leafCount = 0;
      varSum = 0.0;
    }
    
    virtual void onNode(char v, bool leftExists, bool rightExists) override {
      if( !(leftExists || rightExists) ){
        leafCount++;
        varSum += ((curdepth - depthMean) * (curdepth - depthMean));
      }
    }
    
    inline virtual void onDownToChild(bool isRightChild) override {
      curdepth++;
    }
    
    inline virtual void onUpFromChild(bool isRightChild) override {
      curdepth--;
    }
    
  // PRIVATE FUNCS
  private:
  
  // PRIVATE FIELDS
  private:
    
    int curdepth;
    
    int leafCount;
    
    double varSum;
    
    const double depthMean;
  };
} /* end of namespace lzw */
#endif // LZWPOSTPROCESS_H
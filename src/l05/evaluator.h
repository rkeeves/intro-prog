
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include "parser.h"

namespace calc{
  class Evaluator{
  public:
    double eval(Node* root, VariableMap &varmap){
      return root->eval(varmap);
    }
  };
} /* end of namespace calc */
#endif // EVALUATOR_H
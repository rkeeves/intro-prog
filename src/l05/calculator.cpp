// 
// Simple Calculator for lab purposes
// 
// Usage examples:
// 
// (1) - Variables declaration
// > let a = 7.6e4;
// 
// (2) - Expression evaluation
// > let a = 7.6e4;
// > a*-1.1;
// 
// (3)- Visualizing TokenStream and parser tree root node
// > tokens;
// > tree;
// > let a = 7.6e4;
// > a*-1.1;
// 
// Related:
// + Simple C++17 Lexer         - https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20
// + GNU Bison                  - https://www.gnu.org/software/bison/
// + Simple language in Python  - https://github.com/andybalaam/cell/blob/master/pycell/parser.py
//
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include <iterator>

using namespace calc;

const std::string IN_HEADER =          "============\n"
                                        "=Input\n"
                                        "============\n";
const std::string TOKENSTREAM_HEADER =  "============\n"
                                        "=TokenStream\n"
                                        "============\n";
const std::string SYNTAXTREE_HEADER =   "============\n"
                                        "=SyntaxTree\n"
                                        "============\n";
const std::string PROMPT = "> ";
const std::string RESULT = "= ";
const std::string OPT_QUIT = "quit";
const std::string OPT_IN = "input";
const std::string OPT_TOKENS = "tokens";
const std::string OPT_TREE = "tree";
const std::string OPT_CLEARMEM = "clearmem";

const double CALC_PI = 3.14159265358979323846;


void calculate()
{ 
  Lexer lexer;
  Parser parser;
  Node* root = nullptr;
  VariableMap m;
  m["pi"] = CALC_PI;
  Evaluator eval;
  bool show_in = false;
  bool show_tokens = false;
  bool show_tree = false;
	while(true){
    try 
    {
      std::cout << PROMPT;
      std::string txt;
      if (std::getline(std::cin, txt))
      {
        if(txt.compare(OPT_QUIT)==0)
          break;
        else if(txt.compare(OPT_TOKENS)==0)
          show_tokens = !show_tokens;
        else if(txt.compare(OPT_TREE)==0)
          show_tree = !show_tree;
        else if(txt.compare(OPT_IN)==0)
          show_in = !show_in;
        else if(txt.compare(OPT_CLEARMEM)==0)
          m.clear();
        else{
          TokenStream tokstream = lexer.lex(&txt);
          if(show_in)
            {std::cout << IN_HEADER << txt << std::endl;}
          if(show_tokens)
            {std::cout << TOKENSTREAM_HEADER << tokstream;}
          root = parser.parse(&tokstream);
          if(show_tree)
            {std::cout << SYNTAXTREE_HEADER; root->serialize(1,std::cout);}
          std::cout << RESULT <<  eval.eval(root,m) << std::endl ;
          if(root)
            delete root;
        }
      }
    }
    catch(std::runtime_error& e) 
    {
      std::cerr << std::endl << "[ERROR] " << e.what() << std::endl;
    }
  } 
}

int main() 
{
  try {
		calculate();
		return 0;
	}
  catch (std::exception& e) 
  {
		std::cerr << "exception: " << e.what() << std::endl;
		char c;
		while (std::cin >>c&& c!=';') ;
		return 1;
	}
	catch (...) 
  {
		std::cerr << "exception\n";
		char c;
		while (std::cin>>c && c!=';');
		return 2;
	}
}
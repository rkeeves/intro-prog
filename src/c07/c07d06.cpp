// based on http://www.stroustrup.com/Programming/calculator00.cpp
/*
    Statement:
        Declaration
        Expression
    
    Declaration:
        "let" Name "=" Expression

    Print:
        ;

    Quit:
        q 

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        Name
          Name = Expression
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal
*/
#include "../std_lib_facilities_modded.h"

const string KEYWORD_LET = "let";
const string KEYWORD_QUIT = "quit";

const char KIND_LET = 'L';      // Let kind token
const char KIND_QUIT = 'Q';     // Quit kind token
const char KIND_PRINT = ';';    // Print kind token
const char KIND_NUMBER = '8';   // Number kind token
const char KIND_NAME = 'a';     // Name kind token

const string STR_PROMPT = "> "; // The prompt to signal user input is needed
const string STR_RESULT = "= "; // The string before the evaluated expression's result

struct Token {
	Token(char ch) :kind(ch), value(0), name("") { }
	Token(char ch, double val) :kind(ch), value(val), name("") { }
  Token(char ch, string n) :kind(ch), value(0), name(n) { }
  char kind;      // kind of token
	double value;   // raw string value
	string name;    // parsed double value
};

class Token_stream {
public:
	Token_stream() : full(0), buffer(0) { }
	Token get();          // get the next Token
	void unget(Token t);  // Put back a token (to buffer)
	void ignore(char);    // discard tokens up to an including a char
private:
	bool full;        // if true the next token returned by get will be the buffer.
	Token buffer;     // internal buffered token. Used to implement unget.
};

// Puts back a token (to buffer)
void Token_stream::unget(Token t)
{ 
  if (full) error("unget() called but buffer was already full");
  buffer=t; 
  full=true; 
}

// Extracts the next Token or gets it from the buffer if possible.
Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
  
	char ch;
	cin >> ch;
  
  if(ch == '.' || isdigit(ch)){	
    cin.unget();
		double val;
		cin >> val;
		return Token(KIND_NUMBER,val);
	};
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
		return Token(ch);
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (ch=='_' || isalpha(ch) || isdigit(ch))) s+=ch;
			cin.putback(ch);
			if (s == KEYWORD_LET) return Token(KIND_LET);	
			if (s == KEYWORD_QUIT) return Token(KIND_QUIT);
			return Token(KIND_NAME,s);
		}
		error("Bad token");
	}
}

// Extracts characters from cin until the argument char's first occurrence,
// including the first occurrence of the char itself.
void Token_stream::ignore(char c)
{
	if (full &&  c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch;
	while (cin>>ch) if (ch==c) return;
}

Token_stream ts;

// Represents a name, value pair.
// During evaluation these store a variable's name and associated value.
struct Variable {
	Variable(string n, double v) :name(n), value(v) { }
  string name;
	double value;
};

vector<Variable> names;	

// Gets the value of the variable by the specified name.
double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

// Sets the value of the variable by the specified name to the specified value.
void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}
// Checks whether a variable by the specified name exists already.
bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

double expression(); // forward decl for primary

// Parses a primary.
// A primary can be any of the following:
// - an expression between "(" and ")"
// - a negation of a primary
// - a token of kind number, having a double value
// - a token of kind name, having the string raw value of an already declared variable name
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
    double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
    return d;
	}
  case '-':
      return - primary();
  case '+':
      return primary();
	case KIND_NUMBER:
		return t.value;
	case KIND_NAME:
  {
    Token temp = ts.get();
    if (temp.kind == '=') {	// handle name = expression
      double d = expression();
      set_value(t.name,d);
      return d;
    } else {
      ts.unget(temp);
      return get_value(t.name);
    }
  }
	default:
		error("primary expected");
	}
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while(true) {
      switch (t.kind) {
      case '*':
      {
        left *= primary();
        t = ts.get();
        break;
      }
          
      case '/':
      {    
          double d = primary();
          if (d == 0) error("divide by zero");
          left /= d; 
          t = ts.get();
          break;
      }
      case '%':
      {    
          int lhs_i = narrow_cast<int>(left);
          int rhs_i = narrow_cast<int>(term());
          if (rhs_i == 0) error("%: divide by zero");
          left = lhs_i%rhs_i; 
          t = ts.get();
          break;
      }
      default: 
        ts.unget(t);
        return left;
      }
    }
}
// Evaluates an expression
double expression()
{
    double left = term();
    Token t = ts.get();
    while(true) {    
        switch(t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default: 
            ts.unget(t);
            return left;
        }
    }
}
// Evaluates a declaration.
// A declaration must follow the form:
// let <varname> = <expression>
double declaration()
{
	Token t = ts.get();
	if (t.kind != KIND_NAME) error ("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;
}
// Evaluates a statement.
// If the first token is of let kind it tries to parse as declaration,
// otherwise as an expression.
double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case KIND_LET:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

/*
  Clears the tokenstream's underlying istream (cin) until ite reaches the print kind char.
*/
void clean_up_mess()
{
	ts.ignore(KIND_PRINT);
}

void calculate()
{  
  // Added k variable
  names.push_back(Variable("k",1000.0));
	while(true) 
  {
    try {
      cout << STR_PROMPT;
      Token t = ts.get();
      while (t.kind == KIND_PRINT) t=ts.get();
      if (t.kind == KIND_QUIT) return;
      ts.unget(t);
      double res = statement();
      cout << STR_RESULT << res << endl;
    }catch(runtime_error& e) {
      cerr << e.what() << endl;
      clean_up_mess();
    }
  }
}

int main()
{
  try {
		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >>c && c!=';') ;
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c != ';');
		return 2;
	}
}

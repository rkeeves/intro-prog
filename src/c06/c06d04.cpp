/*
  See Original at
  http://www.stroustrup.com/Programming/calculator02buggy.cpp
  Erased all original comments except for decription about bugs.
  Fixed all bugs, and commented them.
*/
/*
	This file is known as calculator02buggy.cpp

	I have inserted 5 errors that should cause this not to compile
	I have inserted 3 logic errors that should cause the program to give wrong results

	First try to find an remove the bugs without looking in the book.
	If that gets tedious, compare the code to that in the book (or posted source code)

	Happy hunting!

*/
const char EXIT_CHAR = 'x';
const char PRINT_CHAR = '=';
#include "../std_lib_facilities.h"
/****************************************
 COMPILE TIME ERROR 1
*****************************************
lass Token
*/
class Token {
public:
    char kind;
    double value;
    Token(char ch)
        :kind(ch), value(0) { }    
    Token(char ch, double val)
        :kind(ch), value(val) { }
};

class Token_stream {
public: 
    Token_stream();
    Token get();
    void putback(Token t);
private:
    bool full;
    Token buffer;
};


Token_stream::Token_stream()
:full(false), buffer(0)
{
}

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;
    full = true;
}
/****************************************
 COMPILE TIME ERROR 2
*****************************************
Token get()
*/
Token Token_stream::get()
{
    if (full) {   
        full=false;
        return buffer;
    } 

    char ch;
    cin >> ch;

    switch (ch) {
    case PRINT_CHAR:
    case EXIT_CHAR:
    case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);
/****************************************
 LOGIC ERROR 1
*****************************************
case 8 was missing
*/        
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            cin.putback(ch);  
            double val;
            cin >> val;     
            return Token('8',val); 
        }
    default:
        error("Bad token");
    }
}

Token_stream ts;

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(': 
        {    
            double d = expression();
            t = ts.get();
/****************************************
 COMPILE TIME ERROR 3
*****************************************
if (t.kind != ')') error("')' expected);
*/
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case '8':           
        return t.value;
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
            left *= primary();
            t = ts.get();
/****************************************
 LOGIC ERROR 2
*****************************************
break after case was missing
*/
            break;
        case '/':
            {    
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
        default: 
            ts.putback(t);
            return left;
        }
    }
}


double expression()
{
/****************************************
 COMPILE TIME ERROR 4
*****************************************
double left = term(;
*/
    double left = term(); 
    Token t = ts.get();
    while(true) {    
        switch(t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
/****************************************
 LOGIC ERROR 3
*****************************************
left += term();
*/
            left -= term(); 
            t = ts.get();
            break;
        default: 
            ts.putback(t);
            return left;
        }
    }
}

int main()
try
{
/****************************************
 COMPILE TIME ERROR 5
*****************************************
variable by name of "val" of type double was used but not declared (also not inited).
*/
  double val = 0.0;
  cout << "Welcome to our simple calculator!" << endl;
  cout << "Please enter expressions using floating-point numbers!"  << endl;
    while (cin) {
        Token t = ts.get();
        if (t.kind == EXIT_CHAR) break;
        if (t.kind == PRINT_CHAR)
            cout << "=" << val << '\n';
        else
            ts.putback(t);
        val = expression();
    }
	keep_window_open();
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n'; 
	keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n"; 
	keep_window_open();
    return 2;
}
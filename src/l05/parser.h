#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cmath>
#include <iostream>
#include <set>
namespace calc{

  typedef std::map<std::string,double> VariableMap;
  
  class Node{
  public:
    virtual ~Node() { }
    
    virtual double eval(VariableMap &varMap) = 0;
    
    void serialize(int n, std::ostream& os)  {
      std::string s = graphicSymbol();
      os << std::string( n, ' ' ) << s << std::endl;
      if(ln() != nullptr){
        ln()->serialize(n+1,os);
      }
      if(rn() != nullptr){
        rn()->serialize(n+1,os);
      }
    }
    
    virtual std::string graphicSymbol(){ return "Node"; }
    
    virtual Node* ln(){ return nullptr; }
  
    virtual Node* rn(){ return nullptr; }
  };
  
  class UniExp : public Node{
  public:
    UniExp(Node* node) : m_n(node){}
    
    ~UniExp(){ delete m_n; };
    
    virtual Node* ln() override{ return m_n; }
    
  protected:
    Node* m_n;
  };

  class Identity : public UniExp{
  public:
    Identity(Node* node) : UniExp(node){}
    
    virtual std::string graphicSymbol() override{ return "Identity"; }
    
    virtual double eval(VariableMap &varMap){
      return m_n->eval(varMap);
    }
   
  };

  class Negate : public UniExp{
  public:
    Negate(Node* node) : UniExp(node){}
    
    virtual std::string graphicSymbol() override{ return "Negate"; }
    
    virtual double eval(VariableMap &varMap){
      return -(m_n->eval(varMap));
    }
  };

  class BinExp : public Node{
  public:
    BinExp(Node* left,Node* right) : m_l(left),m_r(right){}

    ~BinExp(){ delete m_l; delete m_r; };
    
    virtual Node* ln(){ return m_l; }
  
    virtual Node* rn(){ return m_r; }
  protected:
    Node* m_l;
    
    Node* m_r;
  };
  
  class Add : public BinExp{
  public:
    Add(Node*left,Node*right) :BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Add"; }
    
    virtual double eval(VariableMap &varMap) override {
      return m_l->eval(varMap) + m_r->eval(varMap);
    }
  };

  class Subtract : public BinExp{
  public:
    Subtract(Node*left,Node*right) :BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Subtract"; }
    
    virtual double eval(VariableMap &varMap) override {
      return m_l->eval(varMap) - m_r->eval(varMap);
    }
  };

  class Multiply : public BinExp{
  public:
    Multiply(Node*left,Node*right) :BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Multiply"; }
    
    virtual double eval(VariableMap &varMap) override {
      return m_l->eval(varMap) * m_r->eval(varMap);
    }
  };

  class Divide : public BinExp{
  public:
    Divide(Node*left,Node*right) :BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Divide"; }
    
    virtual double eval(VariableMap &varMap) override {
      double r = m_r->eval(varMap);
      if(r == 0.0)
        {throw std::runtime_error("Division by 0");}
      return m_l->eval(varMap) / m_r->eval(varMap);
    }
  };
  
  class Pow : public BinExp{
  public:
    Pow(Node*left,Node*right) : BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Pow"; }
    
    virtual double eval(VariableMap &varMap) override {
      return pow( m_l->eval( varMap ), m_r->eval( varMap ) ) ;
    }
  };
  
  class Mod : public BinExp{
  public:
    Mod(Node*left,Node*right) : BinExp(left,right)  {}
    
    virtual std::string graphicSymbol() override{ return "Mod"; }
    
    virtual double eval(VariableMap &varMap) override {
      return fmod( m_l->eval( varMap ), m_r->eval( varMap ) ) ;
    }
  };
  
  class Constant : public Node{
  public:
    Constant(double d) : m_d(d)  {}
    
    virtual std::string graphicSymbol() override{ 
      std::ostringstream strs;
      strs << "Constant("<< m_d<<")";
      return strs.str();
    }
    
    virtual double eval(VariableMap &varMap) override {
      return m_d;
    }
    
  private:
    double m_d;
  };
  
  class Identifier : public Node{
  public:
    Identifier(std::string name) : m_name(name) {}
    
    virtual std::string graphicSymbol() override{ 
      std::ostringstream strs;
      strs << "Identifier('"<< m_name<<"')";
      return strs.str();
    }
    
    virtual double eval(VariableMap &varMap) override {
        auto it = varMap.find(m_name);
        if (it != varMap.end()){
          return it->second;
        }else{
          std::ostringstream strs;
          strs << "Identifier '"<< m_name<<"' undefined";
          throw std::runtime_error(strs.str());
        }
    }
    
    const std::string &var(){
      return m_name;
    }
  private:
    std::string m_name;
  };
  
  class Assignment : public Node{
  public:
    Assignment(Identifier* id,Node*right) : m_id(id), m_right(right) {}
    
    ~Assignment(){ delete m_id; delete m_right; };
    
    virtual std::string graphicSymbol() override{ return "Assignment"; }
    
    virtual double eval(VariableMap &varMap) override {
      double d = (m_right->eval(varMap));
      varMap[m_id->var()] = d ;
      return d;
    }
    
    virtual Node* ln(){ return m_id; }
  
    virtual Node* rn(){ return m_right; }
    
  private:
    Identifier* m_id;
    
    Node* m_right;
  };
  
  class Parser{
    
  public:
    Parser(){};
    
    Node* parse(TokenStream *ts){
      varNameSet.clear();
      m_ts = ts;
      return statement();
    }

    
  private:
    bool isDeclared(const std::string name){
      return (varNameSet.find(name) != varNameSet.end());
    }
  
    Node* expression();

    Node* term();
    
    Node* primary();
    
    Node* declaration();

    Node* statement();
    
  private:
 
    TokenStream *m_ts = nullptr;
    
    std::set<std::string> varNameSet;
  };
  
  Node* Parser::statement()
  {
    Token t =  m_ts->next();
    if(t.kind() == Kind::Let){
      Node* n = declaration();
      Token t1 =  m_ts->next();
      if(t1.kind() != Kind::Semicolon)
      {
        delete n;
        std::ostringstream strs;
        strs << "Statement not closed by semicolon at " << static_cast<int>(t1.pos()) << "!";
        throw std::runtime_error(strs.str());
      }
      return n;
    }else{
      m_ts->putBack(t);
      Node* n = expression();
      Token t1 =  m_ts->next();
      if(t1.kind() != Kind::Semicolon)
      {
        delete n;
        std::ostringstream strs;
        strs << "Statement not closed by semicolon at " << static_cast<int>(t1.pos()) << "!";
        throw std::runtime_error(strs.str());
      }
      return n;
    }
  }
  
  Node* Parser::declaration()
  {
    Token t = m_ts->next();
    if (t.kind() != Kind::Identifier)
    {
      std::ostringstream strs;
      strs << "Variable name was missing in declaration at " << static_cast<int>(t.pos()) << "!";
      throw std::runtime_error(strs.str());
    } 
    std::string name = m_ts->raw(t);
    if (isDeclared(name))
    {
      std::ostringstream strs;
      strs << "Variable with name " << name << " was declared twice at " << static_cast<int>(t.pos()) << "!";
      throw std::runtime_error(strs.str());
    }
    Token t2 = m_ts->next();
    if (t2.kind() != Kind::Equal)
    {
      std::ostringstream strs;
      strs << "= missing in declaration of " << name << " at " << static_cast<int>(t.pos()) << "!";
      throw std::runtime_error(strs.str());
    }
    return new Assignment( new Identifier(name),expression());
  }
  
  Node* Parser::expression()
  {
    Node* left = term();
    while(true) {
      Token t = m_ts->next();
      switch(t.kind()) {
      case calc::Kind::Plus:
        left = new Add(left,term());
        break;
      case calc::Kind::Minus:
        left = new Subtract(left,term());
        break;
      default:
        m_ts->putBack(t);
        return left;
      }
    }
  }

  Node* Parser::term()
  {
    Node* left = primary();
    while(true) {
      Token t = m_ts->next();
      switch(t.kind()) {
        case calc::Kind::Asterisk:
        {
          left = new Multiply(left,primary());
          break;
        }
        case calc::Kind::Slash:
        {	
          left = new Divide(left,primary());
          break;
        }
        default:
        {
          m_ts->putBack(t);
          return left;
        }
      }
    }
  }
    
  Node* Parser::primary()
  {  
    Token t = m_ts->next();
    switch (t.kind()) {
      case calc::Kind::LeftParen:
      {	
        Node* n = expression();
        t = m_ts->next();
        if (t.kind() !=  calc::Kind::RightParen){
          std::ostringstream strs;
          strs << "')' expected at " << static_cast<int>(t.pos()) << "!";
          throw std::runtime_error(strs.str());
        } 
        return n;
      }
      case calc::Kind::Plus:
        return new Identity(primary());
      case calc::Kind::Minus:
        return new Negate(primary());
      case calc::Kind::Number:
        return new Constant(std::stod(m_ts->raw(t)));
      case calc::Kind::Identifier:
        return new Identifier(m_ts->raw(t));
      default:
      {
        std::ostringstream strs;
        strs << "Primary expected at " << static_cast<int>(t.pos()) << "!";
        throw std::runtime_error(strs.str());
      }
    }
  }
} /* end of namespace calc */
#endif // PARSER_H
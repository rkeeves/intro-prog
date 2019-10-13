#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

namespace calc{
  inline bool isSpace(char c) noexcept 
  {
    return ((' ' == c) || ('\t' == c) || ('\r' == c) || ('\n' == c));
  }

  inline bool isDigit(char c) noexcept 
  {
    return (('0' <= c) && (c <= '9'));
  }

  inline bool isAlpha(const char c)
  {
     return (('a' <= c) && (c <= 'z')) ||
            (('A' <= c) && (c <= 'Z')) ;
  }
  
  inline bool isValidIdentifierBegin(const char c)
  {
     return isAlpha(c);
  }

  inline bool isValidIdentifierNonBegin(char c) noexcept {
    return (isAlpha(c) || isDigit(c) || (c == '_') );
  }
  
  enum class Kind {
    Number,
    Identifier,
    LeftParen,
    RightParen,
    Equal,
    Plus,
    Minus,
    Asterisk,
    Slash,
    Mod,
    Semicolon,
    Let,
    End,
    Unexpected,
  };
  
  std::ostream& operator<<(std::ostream& os, const calc::Kind& kind) {
    static const char* const names[]{
      "Number",
      "Identifier",
      "LeftParen",
      "RightParen",
      "Equal",
      "Plus",
      "Minus",
      "Asterisk",
      "Slash",
      "Mod",
      "Semicolon",
      "Let",
      "End",
      "Unexpected",
    };
    return os << names[static_cast<int>(kind)];
  }

  
  const std::map<std::string,Kind> keyWords { 
    {"let",Kind::Let}
  };
    
  Kind getKindForPredefinedKeyword(const std::string &s){
    std::map<std::string,Kind>::const_iterator it = keyWords.find(s);
    if (it != keyWords.end())
      return it->second;
    else 
      return Kind::Unexpected;
  }
  
  class Token {
    
  public:
    
    Token(calc::Kind kind, size_t pos, size_t len) : m_kind(kind), m_pos(pos), m_len(len){};
    
    inline calc::Kind kind() const { return m_kind; };
    
    inline size_t pos() const { return m_pos; };
    
    inline size_t len() const { return m_len; };
    
  private:
    calc::Kind m_kind;
    
    size_t m_pos, m_len; 
  };
  
  class Lexer;
  
  class TokenStream{
    public:
      TokenStream() noexcept : m_str(""), m_full(false), m_buffer(calc::Kind::Unexpected,0,0) {}
    
      TokenStream(std::string *str) noexcept : m_str(*str), m_full(false), m_buffer(calc::Kind::Unexpected,0,0) {}
      
      void reset(){m_buffer=Token(calc::Kind::Unexpected,0,0); m_full=false;m_i=0;};
         
      void putBack(Token t) { m_buffer=t; m_full=true; }
      
      Token next() noexcept{
        if (m_full) { m_full=false; return m_buffer; }
        if(m_tokens.size() > m_i){
          return m_tokens[m_i++];
        }else{
          return Token(calc::Kind::End, m_tokens.size(), 1);
        }
      }

      friend std::ostream& operator<<(std::ostream& os, const TokenStream& ts);
      
      std::string raw(const Token& t) const{ return m_str.substr(t.pos(),t.len()); }
      
    private:
      std::vector<Token> m_tokens;
      
      int m_i = 0;
      
      bool m_full;
    
      Token m_buffer;
      
      std::string m_str;
      
      friend class Lexer;
  };
  
  std::ostream& operator<<(std::ostream& os, const TokenStream& ts)
  {
      for(std::vector<Token>::const_iterator it = ts.m_tokens.begin(); it != ts.m_tokens.end(); ++it) {
          os << std::left << std::setw(12) << (*it).kind() <<  std::left << std::setw(10) << ts.raw(*it) << "\n";
      }
      return os;
  }

  class Lexer {
    
  public:
    Lexer() noexcept {}
    
  public:
  
    TokenStream lex(std::string *str);
    
  private:
  
    Token next() noexcept;

    inline Token atom(calc::Kind kind) noexcept { return Token(kind, m_i++, 1); }
    
    Token number(size_t start);

    Token identifier(size_t start) noexcept;

    inline const char peek() const noexcept
    {
      if(m_str)
        return (m_str->size() <= m_i || m_i < 0) ? '\0' : m_str->at(m_i);
      return '\0';
    }
   
    inline const char get() noexcept
    { 
      if(m_str)
        return (m_str->size() <= m_i || m_i < 0) ? '\0' : m_str->at(m_i++);
       return '\0';
    }
    
    void iterateDigits(size_t start) noexcept;
    
    void iterateFractional(size_t start) noexcept;
    
  private:
    std::string *m_str = nullptr;
    
    size_t m_i = 0;
  };

  TokenStream Lexer::lex(std::string *p_str){
    m_str = p_str;
    m_i = 0; 
    TokenStream tokstream(p_str);
    for (auto t = next(); !(t.kind() == calc::Kind::End);t = next()) {
      if(t.kind() == calc::Kind::Unexpected){
          std::ostringstream strs;
          strs << "Lexer Error: Unexpected token at " << t.pos() << "!";
          throw std::runtime_error(strs.str());
      }
      tokstream.m_tokens.push_back(t);
    }
    return tokstream;
  }
  
  Token Lexer::next() noexcept
  {
    while (calc::isSpace(peek())) get();
    char c = peek();
    if(c == '\0')
      return Token(calc::Kind::End, m_i, 1);
    if(calc::isValidIdentifierBegin(c))
      return identifier(m_i);
    if(calc::isDigit(c))
      return number(m_i);
    /*
    if(c == '+')
    {
      size_t start = m_i;
      get();
      if(calc::isDigit(peek()))
        {return number(start);}
      else
        {return Token(Kind::Plus, start, 1); }
    }
    if(c == '-')
    {
      size_t start = m_i;
      get();
      if(calc::isDigit(peek()))
        {return number(start);}
      else
        {return Token(Kind::Minus, start, 1); }
    }*/

    if(calc::isDigit(c))
      return number(m_i);
    switch (c) {
      case '(':
        return atom(calc::Kind::LeftParen);
      case ')':
        return atom(calc::Kind::RightParen);
      case '=':
        return atom(calc::Kind::Equal);
      case '+':
        return atom(calc::Kind::Plus);
      case '-':
        return atom(calc::Kind::Minus);
      case '*':
        return atom(calc::Kind::Asterisk);
      case '/':
        return atom(calc::Kind::Slash);
      case '%':
        return atom(calc::Kind::Mod);
      case ';':
        return atom(calc::Kind::Semicolon);
      default:
        return atom(calc::Kind::Unexpected);
    }
  }

  Token Lexer::number(size_t start)
  {
    iterateFractional(start);
    if(peek() == 'e'){
      get();
      if(peek() == '-' || peek() == '+'){
        get();
      }
      if(!calc::isDigit(peek()))
      {
          std::ostringstream strs;
          strs << "Lexer Error: Signed exponent abruptly ended at " << static_cast<int>(m_i) << "!";
          throw std::runtime_error(strs.str());
      }
      iterateDigits(start);
    }
    return Token(calc::Kind::Number, start,(m_i-start));
  }
  
  void Lexer::iterateDigits(size_t start) noexcept
  {
    while (calc::isDigit(peek())) get();
  }
    
  void Lexer::iterateFractional(size_t start) noexcept
  {
    iterateDigits(start);
    if(peek() == '.'){
      get();
      iterateDigits(start);
    }
  }

  Token Lexer::identifier(size_t start) noexcept
  {
      get();
      while (calc::isValidIdentifierNonBegin(peek())) get();
      std::string raw = m_str->substr(start, (m_i-start));
      Kind k = getKindForPredefinedKeyword(raw);
      if(k == Kind::Unexpected)
        return Token(calc::Kind::Identifier, start, (m_i-start));
      else
        return Token(k, start, (m_i-start));
  }
} /* end of namespace calc */
#endif // LEXER_H
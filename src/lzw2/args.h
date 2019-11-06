#ifndef ARGS_H
#define ARGS_H


#include <exception>
#include <string>
#include <set>
#include <vector>
#include <map>

namespace lzw{
  // Dumb command line arg handler.
  //
  // Command line args are categorized into:
  //  - argopt : Any string starting with '-'
  //  - argvalue : Any string not starting with '-'
  //
  // Argvalues are associated to argopts by the following rules:
  //  - if an argvalue's predecessor in the arg array was an argopt,
  //    the argvalue will become an element of the argopt
  //  - if an argvalue's predecessor was an element of an argopt,
  //    then the current argvalue will become an element of that argopt
  //  - otherwise the argvalue will become an element of the default argopt.
  //    This default argopt is referred as ""
  // 
  // Example:
  // a.o b -c d -e f g -h
  // Opt    Elements
  // ""     {"a.o","b"}
  // "-c"   {"d"}  
  // "-e"   {"f","g"}
  // "-h"   {}
  //
  class Args{
    
  // LIFECYCLE
  public:
    Args(int argc, char **argv) : argc(argc), argv_head(argv){
      parse();
    };
    
    ~Args(){};
    
  private:
  
    Args (const Args &);
    
    Args & operator= (const Args &);
  // PUBLIC FUNCS
  public: 

    const std::string DEFAULT_OPT_KEY = "";
  
    int count() const;
    
    const std::string operator[](int i) const;

    bool hasOpt(const std::string &opt) const;

    const std::vector<std::string> &getOpt() const;
    
    const std::vector<std::string> & operator[](const std::string &opt) const;
  
  // PRIVATE FUNCS
  private:
  
    void parse();

    bool isOpt(const std::string &s) const;
  // PRIVATE FIELDS
  private:

    int argc;

    char **argv_head;
  
    std::map<std::string,std::vector<std::string>> optvals;
  };
  
  int Args::count() const
  {
    return argc;
  }
  
  const std::string Args::operator[](int i) const
  {
    if(i < argc){
      return std::string(*(argv_head+i));
    }else{
      throw std::runtime_error("Specified argument index was out of bounds");
    }
  }
    
  bool Args::hasOpt(const std::string &opt) const
  {
    return optvals.find(opt) != optvals.end();
  }

  const std::vector<std::string> & Args::getOpt() const
  {
    return optvals.find(DEFAULT_OPT_KEY)->second;
  }
  
   const std::vector<std::string> & Args::operator[](const std::string &opt) const
  {
    auto it = optvals.find(opt);
    if(it == optvals.end()){
       throw std::runtime_error("Specified opt did not exist");
    }else{
      return it->second;
    }
  }

  void Args::parse()
  {
    optvals[DEFAULT_OPT_KEY] = std::vector<std::string>();
    char **cur_arg_ptr = argv_head;
    std::string lastGroup = DEFAULT_OPT_KEY;
    for(int i = 0; i < argc; ++i){
      std::string s(*cur_arg_ptr);
      if(isOpt(s)){
        optvals[s] = std::vector<std::string>();
        lastGroup = s;
      }else{
        optvals[lastGroup].push_back(s);
      }
      cur_arg_ptr++;
    }
  }
    
  bool Args::isOpt(const std::string &s) const
  {
    return (s.size() > 1 && s[0] == '-');
  }
} /* end of namespace lzw */
#endif // ARGS_H
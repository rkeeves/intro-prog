#include "args.h"
#include "rawptrtree.h"
#include "lzwpostprocess.h"
#include "lzwio.h"

using namespace lzw;

void usage (void)
{
  std::cout << "Binary tree reader/writer for Lempel-Ziv-Welch algorithm" << std::endl;
  std::cout << "Usage: lzwtree [IN_FILE] -o [OUT_FILE]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  " << "-o,  output file to write" << std::endl;
  std::cout << "  " << "-m,  max bytes to read" << std::endl;
  std::cout << "  " << "-l,  treat '0' as 0 all else as '1' from input" << std::endl;
}

void handleArgs(int argc, char **argv, std::string &inFName, std::string &outFName, int &maxbytes, bool &sourceIsLiteralBinary){
  Args args(argc,argv);
  auto optPos = args[""];
  if(optPos.size() != 2){
    throw std::runtime_error("Input file was NOT specified!");
  }
  inFName = optPos[1];
  if(!args.hasOpt("-o")){
    throw std::runtime_error("Output file was NOT specified!");
  }
  auto optO = args["-o"];
  if(optO.size() != 1){
    throw std::runtime_error("Output file was NOT specified!");
  }
  outFName= optO[0];
  if(args.hasOpt("-m")){
    auto optBytes = args["-m"];
    if(optBytes.size() != 1){
      throw std::runtime_error("Bad maxbytes option!");
    }else{
      try{
        maxbytes = std::stoi( optBytes[0] );
        
      }catch(...){
        throw std::runtime_error("Bad maxbytes option!");
      }
      if(maxbytes < 1){
        throw std::runtime_error("Bad maxbytes option!");
      }
    }
  }
  if(args.hasOpt("-l")){
    sourceIsLiteralBinary = true;
  }
  return;
}

int main(int argc, char **argv){
  std::string inFName;
  std::string outFName;
  int maxbytes = -1;
  bool sourceIsLiteralBinary = false;
  
  try{
    handleArgs(argc, argv, inFName,outFName, maxbytes,sourceIsLiteralBinary) ;
  }catch(const std::exception &e){
    std::cerr << "[ARGUMENT_ERROR] " << e.what() << std::endl << std::endl;
    usage ();
    return -1;
  }catch(...){
    std::cerr << "[ARGUMENT_ERROR] " << "Unknown error during argument parsing!" << std::endl << std::endl;
    usage ();
    return -2;
  }
  
  std::fstream inFile (inFName, std::ios_base::in);
  if (!inFile){
      std::cerr << "[IN_FILE_ERRROR]" << "Input file '" << inFName << "' does not exist!" << std::endl << std::endl;
      usage ();
      return -3;
  }
  
  RawPtrTree rawptrtree;

  fillFromFile(inFile,rawptrtree,sourceIsLiteralBinary,maxbytes);
  inFile.close ();

  std::fstream outFile (outFName, std::ios_base::out);
  writeToFile(outFile,rawptrtree);
  outFile.close ();
  
  return 0;
}
#include "llvm/Bitcode/ReaderWriter.h" 
#include "llvm/IR/Function.h" 
#include "llvm/IR/Module.h" 
#include "llvm/Support/CommandLine.h" 
#include "llvm/Support/MemoryBuffer.h" 
#include "llvm/Support/raw_os_ostream.h" 
#include "llvm/Support/raw_ostream.h" 
//#include "llvm/Support/system_error.h" 
#include <iostream>
#include <string>

using namespace std;
using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

int main(int argc, char* argv[]){
  cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");
  LLVMContext context;
  std::string error;
  llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> mb= MemoryBuffer::getFile(FileName);
  ErrorOr<std::unique_ptr<Module>> mOrErr = parseBitcodeFile(mb.get()->getMemBufferRef(), context);
  if (std::error_code EC = mOrErr.getError()) {
    std::cerr<<"Error reading bitcode:" << error << std::endl;
    return -1;
  }
  /*if(m == 0){
    std::cerr<<"Error reading bitcode:" << error << std::endl;
    return -1;
  }*/
  std::unique_ptr<Module> m = std::move(mOrErr.get());
  raw_os_ostream O( std:: cout);
  for (Module::const_iterator i = m->getFunctionList().begin(), e = m->getFunctionList(). end(); i != e; ++i) { 
    if (! i->isDeclaration()){ 
      O << i->getName() << " has " << i->size() << " basic block( s).\n"; 
    } 
  } 
  return 0;
}

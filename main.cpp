#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>


int main() {
  llvm::LLVMContext context;
  llvm::Module *module = new llvm::Module("hello", context);
  llvm::IRBuilder<> builder(context);

  llvm::FunctionType *main_type =
      llvm::FunctionType::get(builder.getInt32Ty(), false);
  llvm::Function *main_function = llvm::Function::Create(
      main_type, llvm::Function::ExternalLinkage, "main", module);
  llvm::BasicBlock *entry_bb =
      llvm::BasicBlock::Create(context, "entry", main_function);
  builder.SetInsertPoint(entry_bb);

  std::vector<llvm::Type *> printf_args;
  printf_args.push_back(builder.getInt8PtrTy());
  llvm::FunctionType *printf_type =
      llvm::FunctionType::get(builder.getInt32Ty(), printf_args, true);
  llvm::FunctionCallee printf =
      module->getOrInsertFunction("printf", printf_type);

  llvm::Value *format_str = builder.CreateGlobalStringPtr("Hello, World!\n");

  builder.CreateCall(printf, {format_str});

  builder.CreateRet(builder.getInt32(0));

  verifyModule(*module, &llvm::errs());

  module->print(llvm::outs(), nullptr);

  delete module;

  return 0;
}

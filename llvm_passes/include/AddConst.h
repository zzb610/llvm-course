#ifndef ADD_CONST_H
#define ADD_CONST_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"

namespace addconst {

// An analysis traverses a function add collects
// all the "add" instructions with const operand
struct AddConstAnalysis : public llvm::AnalysisInfoMixin<AddConstAnalysis> {
  using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
  // pass working scope is Function
  Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
  static llvm::AnalysisKey Key;
};

struct AddConstPrinterPass : public llvm::PassInfoMixin<AddConstPrinterPass> {
  explicit AddConstPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &FAM);

private:
  llvm::raw_ostream &OS;
};

struct AddConstPass : public llvm::PassInfoMixin<AddConstPass> {
  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &FAM);
};

} // namespace addconst

#endif /* ADD_CONST_H */

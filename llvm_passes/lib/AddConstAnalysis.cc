#include "AddConst.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"

namespace addconst {

// If all operands are contant
bool isConstantOnly(llvm::Instruction &I) {
  for (auto &Op : I.operands()) {
    if (!llvm::isa<llvm::Constant>(Op)) {
      return false;
    }
  }
  return true;
}

// Initialize the analysis key
llvm::AnalysisKey AddConstAnalysis::Key;

AddConstAnalysis::Result
AddConstAnalysis::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM) {

  llvm::SmallVector<llvm::BinaryOperator *, 0> AddInsts;
  for (llvm::BasicBlock &BB : F) {
    for (llvm::Instruction &I : BB) {
      if (!I.isBinaryOp()) {
        continue;
      }
      if (!(I.getOpcode() == llvm::Instruction::BinaryOps::Add)) {
        continue;
      }
      if (!isConstantOnly(I)) {
        continue;
      }

      AddInsts.push_back(&llvm::cast<llvm::BinaryOperator>(I));
    }
  }

  return AddInsts;
}


llvm::PreservedAnalyses AddConstPrinterPass::run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM){
  auto& AddInsts = FAM.getResult<AddConstAnalysis>(F);
  OS << "====================================================\n";
  OS << "|| " << F.getName() << " ||\n";
  OS << "====================================================\n";
  for(auto &Add: AddInsts){
    OS << *Add << "\n";
  }
  OS << "====================================================\n";
  return llvm::PreservedAnalyses::all();
}
} // namespace addconst

#include "AddConst.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

namespace addconst {

void ReplaceAddInstWithConstant(llvm::BinaryOperator *BO) {
  assert(BO->getOpcode() == llvm::BinaryOperator::Add);
  auto first = llvm::cast<llvm::ConstantInt>(BO->getOperand(0));
  auto second = llvm::cast<llvm::ConstantInt>(BO->getOperand(1));
  auto sum = llvm::ConstantExpr::getAdd(first, second);

  BO->replaceAllUsesWith(sum);
  BO->eraseFromParent();
}

llvm::PreservedAnalyses AddConstPass::run(llvm::Function &F,
                                          llvm::FunctionAnalysisManager &FAM) {
  auto &AddInsts = FAM.getResult<AddConstAnalysis>(F);
  for (auto BO : AddInsts) {
    // constant folding
    ReplaceAddInstWithConstant(BO);
  }
  auto PA = llvm::PreservedAnalyses::all();
  // other pass need run AddConstAnalysis again
  PA.abandon<AddConstAnalysis>();
  return PA;
}
} // namespace addconst
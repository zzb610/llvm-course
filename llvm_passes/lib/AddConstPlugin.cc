// This point is the entry point for the new PassManager opt plugin
// it contains the new PassManger registration for all the analysis and
// transformations relate to the AddConst plugin

#include "AddConst.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace llvm {
void registerAnalyses(FunctionAnalysisManager &FAM) {
  FAM.registerPass([] { return addconst::AddConstAnalysis(); });
}

bool registerPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
  if (Name == "print<add-const>") {
    FPM.addPass(addconst::AddConstPrinterPass(errs()));
    return true;
  }
  return false;
}

PassPluginLibraryInfo getAddConstPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "AddConst", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            // 1.register the AddConstAnalysis as an analysis pass
            // it can be requested by other passes as following:
            // FPM.getResult<AddConstAnalysis>(F)
            // FPM is the FunctionAnalysisManager
            // F is the Function that shall be analyzed
            PB.registerAnalysisRegistrationCallback(registerAnalyses);

            // register the AddConstPrinterPass as "print<add-const>"
            // so it can be used when specifying pass pipelines with "-passes="
            // also register AddConstPass as "add-const"
            PB.registerPipelineParsingCallback(registerPipeline);
          }};
}

// The public entry point for a pass plugin
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getAddConstPluginInfo();
}

} // namespace llvm

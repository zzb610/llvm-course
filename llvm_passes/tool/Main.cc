#include "AddConst.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h" // SMDiagnostic

static llvm::cl::OptionCategory AddConstCategory("addconst pass options");

static llvm::cl::opt<std::string>
    InputModule(llvm::cl::Positional, llvm::cl::desc("<Input module>"),
                llvm::cl::value_desc("bitcode filename"), llvm::cl::init(""),
                llvm::cl::Required, llvm::cl::cat(AddConstCategory));

static llvm::cl::opt<std::string>
    OutputModule("o", llvm::cl::Positional, llvm::cl::desc("<Output module>"),
                 llvm::cl::value_desc("bitcode filename"),
                 llvm::cl::init("out.ll"), llvm::cl::cat(AddConstCategory));

int main(int Argc, char **Argv) {

  llvm::cl::HideUnrelatedOptions(AddConstCategory);

  llvm::cl::ParseCommandLineOptions(
      Argc, Argv, "evaluate constant add instructions at compile time.\n");

  llvm::llvm_shutdown_obj SDO;

  llvm::SMDiagnostic Err;
  llvm::LLVMContext Ctx;
  std::unique_ptr<llvm::Module> M =
      llvm::parseIRFile(InputModule.getValue(), Err, Ctx);

  if (!M) {
    llvm::errs() << "Error reading bitcode file: " << InputModule << "\n";
    Err.print(Argv[0], llvm::errs());
    return -1;
  }

  // TODO(zzb): compile failed.
  // addconst::AddConstPass Pass; 
  // llvm::FunctionPassManager FPM;
  // FPM.addPass(Pass);

  llvm::FunctionAnalysisManager FAM;
  FAM.registerPass([&] { return addconst::AddConstAnalysis(); });

  llvm::PassBuilder PB;
  PB.registerFunctionAnalyses(FAM);

  // Transform
  // for (llvm::Function &F : *M) {
  //   FPM.run(F, FAM);
  // }

  std::error_code EC;
  llvm::raw_fd_ostream OS(OutputModule.getValue(), EC);

  if (EC) {
    llvm::errs() << "Couldn't open " << OutputModule.getValue() << ": "
                 << EC.message() << "\n";
    return -1;
  }

  M->print(OS, nullptr);
  OS.close();
  return 0;
}

 
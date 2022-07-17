add_executable(addconst Main.cc ../lib/AddConstAnalysis.cc ../lib/AddConstPass.cc)

target_link_libraries(addconst LLVMCore LLVMIRReader LLVMPasses LLVMSupport)

target_include_directories(addconst PRIVATE "../include")

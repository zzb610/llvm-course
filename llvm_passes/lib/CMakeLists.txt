add_library(AddConst MODULE AddConstAnalysis.cc AddConstPlugin.cc)

target_include_directories(AddConst PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
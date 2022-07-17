cmake_minimum_required(VERSION 3.13.4)
project(llvm-addconst)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ====================================================================
# 1. verify llvm installation dir
# ====================================================================
set(LLVM_INSTALL_DIR CACHE PATH "LLVM installation directory")

# checking
set(LLVM_INSTALL_INCLUDE "${LLVM_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${LLVM_INSTALL_INCLUDE}")
  message(FATAL_ERROR " LLVM_INSTALL_INCLUDE (${LLVM_INSTALL_INCLUDE}) is invalid.")
endif()

set(LLVM_INSTALL_CMAKE "${LLVM_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake")
if(NOT EXISTS "${LLVM_INSTALL_CMAKE}")
message(FATAL_ERROR " LLVM_INSTALL_CMAKE (${LLVM_INSTALL_CMAKE}) is invalid")
endif()

# =====================================================================
# 2. load llvm configuration
# =====================================================================

# add the location of LLVMConfig.cmake to CMake search paths
list(APPEND CMAKE_PREFIX_PATH "${LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_INSTALL_DIR}")

message("LLVM STATUS: 
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)

# set the llvm header and library paths
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# =====================================================================
# 3. build configuration
# =====================================================================

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (default Debug): " FORCE)
endif()

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fdiagnostics-color=always")

# LLVM is normally built without RTTI. Be consistent with that
if (NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fvisibility-inlines-hidden" SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
if (${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
  
endif()

# set the buid directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# =======================================================================
# 4. add sub targets
# doing this at the end so that all definiations and link/include paths are
# avaialable for the sub-projects
# =======================================================================
add_subdirectory(lib)
add_subdirectory(tool)
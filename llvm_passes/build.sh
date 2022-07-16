
LLVM_INSTALL_DIR=~/projects/llvm-project/build

LLVM_OPT=$LLVM_INSTALL_DIR/bin/opt

cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -G "Ninja" -B build/ .

cd build

cmake --build .
LLVM_INSTALL_DIR=~/projects/llvm-project/build

LLVM_OPT=$LLVM_INSTALL_DIR/bin/opt

$LLVM_OPT -load-pass-plugin build/lib/libAddConst.so \
  -passes="add-const" -S examples/foo2.ll \
  -o examples/foo3.ll

